#include "plugin.hpp"


struct BipolarKnob : Module {
	enum ParamIds {
		KNOB_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		NUM_INPUTS
	};
	enum OutputIds {
		LEVEL_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	BipolarKnob() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(KNOB_PARAM, -5.f, 5.f, 0.f, "Level");
	}

	void process(const ProcessArgs &args) override {
		float knobPosition = params[KNOB_PARAM].getValue();
		outputs[LEVEL_OUTPUT].setVoltage(knobPosition);
	}
};


struct BipolarKnobWidget : ModuleWidget {
	BipolarKnobWidget(BipolarKnob *module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/BipolarKnob.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(15.218, 46.063)), module, BipolarKnob::KNOB_PARAM));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(15.218, 96.812)), module, BipolarKnob::LEVEL_OUTPUT));
	}
};


Model *modelBipolarKnob = createModel<BipolarKnob, BipolarKnobWidget>("BipolarKnob");