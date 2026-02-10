const buildType = require('node-gyp-build');
const bindings = buildType(__dirname);

const { cleanse } = bindings;

module.exports = { cleanse };