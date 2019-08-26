#include "plugin.hpp"


struct Invert : Module {
	enum ParamIds {
		NUM_PARAMS
	};
	enum InputIds {
		INPUT_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		OUTPUT_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	Invert() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
	}

	void process(const ProcessArgs &args) override {
		if  (inputs[INPUT_INPUT].active) {
			outputs[OUTPUT_OUTPUT].setVoltage(inputs[INPUT_INPUT].getVoltage()* -1.f);
		}
		else {
			outputs[OUTPUT_OUTPUT].setVoltage(0);
		}
	}
};


struct InvertWidget : ModuleWidget {
	InvertWidget(Invert *module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Invert.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(15.24, 45.355)), module, Invert::INPUT_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(15.24, 96.812)), module, Invert::OUTPUT_OUTPUT));
	}
};


Model *modelInvert = createModel<Invert, InvertWidget>("Invert");