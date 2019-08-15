#include "plugin.hpp"


struct SimpleKnob : Module {
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

	SimpleKnob() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(KNOB_PARAM, 0.f, 1.f, 0.f, "");
	}

	void process(const ProcessArgs &args) override {
		float knobPosition = params[KNOB_PARAM].getValue();
		outputs[LEVEL_OUTPUT].setVoltage(knobPosition * 10.0f);
	}
};


struct SimpleKnobWidget : ModuleWidget {
	SimpleKnobWidget(SimpleKnob *module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/SimpleKnob.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(15.218, 46.063)), module, SimpleKnob::KNOB_PARAM));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(15.218, 96.812)), module, SimpleKnob::LEVEL_OUTPUT));
	}
};


Model *modelSimpleKnob = createModel<SimpleKnob, SimpleKnobWidget>("SimpleKnob");