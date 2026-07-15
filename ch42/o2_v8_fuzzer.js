// O-2: Browser V8 Fuzzing — JavaScript grammar-based fuzzer
// Run: node o2_v8_fuzzer.js
const FUZZ_ITERATIONS = 10000;

const templates = [
    'let a = {}; a[%d] = %d;',
    'function f(x) { return x + %d; } f(%d);',
    'Array(%d).fill(%d);',
    'new Proxy({}, { get: (t, p) => t[p] = %d });',
    'let b = new ArrayBuffer(%d); new DataView(b).getInt32(%d);',
];

function randomInt(max) {
    return Math.floor(Math.random() * max);
}

function generateTestCase() {
    const tmpl = templates[randomInt(templates.length)];
    return tmpl.replace(/%d/g, () => randomInt(0x1000000).toString());
}

for (let i = 0; i < FUZZ_ITERATIONS; i++) {
    try {
        const code = generateTestCase();
        eval(code);
    } catch (e) {
        // Expected: many test cases will throw
    }
}

console.log(`Generated ${FUZZ_ITERATIONS} test cases`);
