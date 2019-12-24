const path = require('path');
const GccTargetBuilder = require('pango-gcc').GccTargetBuilder;

module.exports = {
  targets: {
    'stm32-utils': {
      run(projectOptions) {
        projectOptions.gcc.includeDirs.push(path.join(__dirname, 'include'));
        return GccTargetBuilder.createTargets(projectOptions, __dirname);
      },
      postRequisites: ['build']
    }
  }
};
