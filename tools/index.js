const { spawn, exec } = require("child_process");
const table = require('markdown-table');
const Observable = require('zen-observable');
const fs = require("fs");
const escape = require('markdown-escape');
const d3output = require("d3node-output");
const d3barchart = require("d3node-barchart");

const RESULT_DIR = "./results";
const BUILD_DIR = "../build";
console.log(`running tests in '${BUILD_DIR}'`);
console.log(`results will be stored in '${RESULT_DIR}'`);

function getNumberOfTests() {
    return new Promise((resolve, reject) => {
        exec("ctest -N", { cwd: BUILD_DIR }, function (err, data) {
            if (err) {
                reject(err);
            } else {
                const regex = /\nTotal Tests: (\d+)/g;
                const match = regex.exec(data);
                if (match != null) {
                    resolve(parseInt(match[1]))
                } else {
                    reject(`cannot match string /\nTotal Tests: (\d+)/g`);
                }
            }
        });
    });
}

function splitTests(testsCount) {
    return new Observable(observer => {
        let storage = Buffer.from([]);
        let currTestCase = 1;
        const ctestProc = spawn("ctest", ["--verbose"], { cwd: BUILD_DIR });
        ctestProc.stdout.on('data', (buf) => {
            storage = Buffer.concat([storage, buf]);
            const start = storage.indexOf(`test ${currTestCase}\n`, "utf8");
            let end = storage.indexOf(`${currTestCase}/${testsCount} Test`, start, "utf8");
            if (end > start) {
                currTestCase++;
                observer.next(storage.toString("utf8", start, end));
                storage = buf;
            }
        });
        ctestProc.on('close', (code) => {
            observer.complete();
        });
    })
}

function parseTestCase(data) {
    const fileName = /Test command: (.+)/g.exec(data)[1];
    return {
        testNr: /test (\d+)/g.exec(data)[1],
        library: /\* TEST: (.+)/g.exec(data)[1],
        name: /\* name\s+: (.+)/g.exec(data)[1],
        info: /\* info\s+: (.*)/g.exec(data)[1],
        dataSize: /\* data size\s+: (.+)/g.exec(data)[1],
        binarySize: fs.statSync(fileName).size,
        serialize: /\* serialize\s+: (.+)/g.exec(data)[1],
        deserialize: /\* deserialize: (.+)/g.exec(data)[1]
    }
}

function generateChart(path, data) {
    return new Promise((resolve, reject) => {
        d3output(path, d3barchart({
            data: data
        }), {}, () => resolve());
    });
}

function generateTable(data) {
    const tableRows = [["library", "test case", "bin size", "data size", "ser time", "des time"]];
    const additionalInfo = [];

    for (let testInfo of data) {
        if (testInfo.info.length > 0) {
            additionalInfo.push(testInfo.info);
        }
        const sub = testInfo.info.length > 0 ? `[<sup>${additionalInfo.length}</sup>](#additional-tests-information)` : ""
        tableRows.push([
            testInfo.library,
            `${testInfo.name}${sub}`,
            `${testInfo.binarySize}B`,
            `${testInfo.dataSize}B`,
            `${testInfo.serialize}ms`,
            `${testInfo.deserialize}ms`
        ]);
    }

    let res = table(tableRows);
    res += "\n\n### Additional tests information\n\n"
    res += additionalInfo.map((info, i) => escape(`${i + 1}. ${info}`)).join("\n");
    return res;
}

getNumberOfTests()
    .then(testsCount => {
        const testsInfo = [];
        return new Promise((resolve, reject) => {
            splitTests(testsCount)
                .map(parseTestCase)
                .subscribe(info => {
                    testsInfo.push(info);
                    console.log(`${info.testNr}/${testsCount}`);
                },
                    err => reject(err),
                    () => resolve(testsInfo));
        });
    })
    .then(data => {
        console.log("\nwriting results");
        if (!fs.existsSync(RESULT_DIR))
            fs.mkdirSync(RESULT_DIR);
        fs.writeFileSync(`${RESULT_DIR}/data.json`, JSON.stringify(data, null, 2));
        fs.writeFileSync(`${RESULT_DIR}/table.md`, generateTable(data));
        // return generateChart(`${RESULT_DIR}/chart.serialize`, data.map(test => ({ key: `${test.library}.${test.name}`, value: test.serialize })))
        // .then(() => generateChart("./chart.datasize", data.map(test => ({ key: `${test.library}.${test.name}`, value: test.dataSize }))))
        // .then(() => generateChart(`${RESULT_DIR}/chart.serialize`, data.map(test => ({ key: `${test.library}.${test.name}`, value: test.deserialize }))))
    })
    .then(() => console.log("complete!"))
    .catch(err => console.log("failed to run tests", err));
