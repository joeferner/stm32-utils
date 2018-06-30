const DefaultComponent = require('pango-components').DefaultComponent;

class STM32Utils extends DefaultComponent {
    constructor() {
        super();
        this.name = 'stm32utils';
    }

    getTasks(projectOptions) {
        const componentOptions = projectOptions.components[this.name];
        return super.getTasks(projectOptions)
            .then(tasks => {
                tasks['stm32utils-build'] = {
                    run() {
                        const compilerOptions = projectOptions.components['gcc'].compilerOptions;
                        if (!componentOptions.debugUART) {
                            return Promise.reject(new Error('Debug UART not specified, run menuconfig first'));
                        }
                        compilerOptions.push(`-DCONFIG_DEBUG_${componentOptions.debugUART}`);
                        return Promise.resolve();
                    },

                    getPrerequisites() {
                        return ['menuconfig-vars'];
                    },

                    getPostRequisites() {
                        return ['compile'];
                    }
                };
                return tasks;
            });
    }

    menuConfig(ctx, componentData) {
        ctx.clear();
        return ctx.inquirer.prompt({
            type: 'list',
            name: 'opt',
            message: 'utils Options',
            choices: [
                `Debug UART (${componentData.debugUART || 'not set'})`,
                new ctx.inquirer.Separator(),
                'Back'
            ]
        }).then(answer => {
            const opt = answer.opt;
            if (opt === 'Back') {
                return componentData;
            }
            if (opt.startsWith('Debug UART')) {
                return this.menuConfigUART(ctx, componentData)
                    .then(uart => {
                        if (uart) {
                            componentData.debugUART = uart;
                        }
                        return this.menuConfig(ctx, componentData);
                    });
            }
            throw new Error(`unhandled option: ${opt}`);
        });
    }

    menuConfigUART(ctx, componentData) {
        ctx.clear();
        return ctx.inquirer.prompt({
            type: 'list',
            name: 'opt',
            message: 'utils Options',
            choices: [
                'UART1',
                'UART2',
                'UART3',
                'UART4',
                'UART5',
                new ctx.inquirer.Separator(),
                'Back'
            ]
        }).then(answer => {
            const opt = answer.opt;
            if (opt === 'Back') {
                return;
            }
            if (opt.startsWith('UART')) {
                return opt;
            }
            throw new Error(`unhandled option: ${opt}`);
        });
    }
}

module.exports = STM32Utils;
