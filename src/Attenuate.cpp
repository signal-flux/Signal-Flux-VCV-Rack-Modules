#include "plugin.hpp"


struct Attenuate : Module {
	enum ParamIds {
		ATTENUATOR_PARAM,
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

	Attenuate() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(ATTENUATOR_PARAM, 0.f, 1.f, 0.f, "");
	}

	void process(const ProcessArgs &args) override {
		if  (inputs[INPUT_INPUT].active) {
			outputs[OUTPUT_OUTPUT].setVoltage(inputs[INPUT_INPUT].getVoltage() * params[ATTENUATOR_PARAM].getValue());
		}
		else {
			outputs[OUTPUT_OUTPUT].setVoltage(0);
		}
	}
};


struct AttenuateWidget : ModuleWidget {
	AttenuateWidget(Attenuate *module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Attenuate.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(20.32, 66.85)), module, Attenuate::ATTENUATOR_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(20.32, 45.355)), module, Attenuate::INPUT_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(20.32, 96.812)), module, Attenuate::OUTPUT_OUTPUT));
	}
};


Model *modelAttenuate = createModel<Attenuate, AttenuateWidget>("Attenuate");