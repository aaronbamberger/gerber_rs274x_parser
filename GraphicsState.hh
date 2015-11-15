#ifndef _GRAPHICS_STATE_H
#define _GRAPHICS_STATE_H

#include <memory>
#include <unordered_map>
#include <string>

#include "GerberClasses/GlobalDefs.hh"
#include "GerberClasses/Point.hh"

// Forward declare some classes to break circular dependencies
class Aperture;
class FormatSpecifier;
class StepAndRepeat;
class ApertureMacro;

class GraphicsState {
public:
	GraphicsState();
	~GraphicsState();

	const std::shared_ptr<FormatSpecifier>& coord_format() const;
    Gerber::UnitType unit_type() const;
    int current_aperture() const;
    Gerber::QuadrantMode current_quadrant_mode() const;
	Gerber::InterpolationMode current_interp_mode() const;
	Gerber::RegionModeState current_region_mode_state() const;
	bool file_complete() const;

	bool set_coord_format(std::shared_ptr<FormatSpecifier> coord_format);
	bool set_unit_type(Gerber::UnitType unit_type);
	bool set_current_aperture(int aperture_num);
	bool define_aperture(int aperture_num, std::shared_ptr<Aperture> aperture_definition);
	bool add_aperture_macro(std::shared_ptr<ApertureMacro> macro);
	bool set_file_complete();
	bool check_aperture_macro(std::string macro_name);

	void set_interp_mode(Gerber::InterpolationMode mode);
	void set_quadrant_mode(Gerber::QuadrantMode mode);
	void set_region_mode_state(Gerber::RegionModeState state);
	void set_step_and_repeat(std::shared_ptr<StepAndRepeat> step_and_repeat);
	void set_level_polarity(Gerber::LevelPolarityType level_polarity);

	const std::shared_ptr<ApertureMacro> lookup_aperture_macro(std::string macro_name);

private:
	std::shared_ptr<FormatSpecifier> m_coord_format;
	Gerber::UnitType m_unit_type;
	int m_current_aperture;
	Gerber::QuadrantMode m_current_quadrant_mode;
	Gerber::InterpolationMode m_current_interp_mode;
	Point<double> m_current_point;
	std::shared_ptr<StepAndRepeat> m_current_step_and_repeat;
	Gerber::LevelPolarityType m_current_level_polarity;
	Gerber::RegionModeState m_current_region_mode_state;
	std::unordered_map<int, std::shared_ptr<Aperture> > m_aperture_dictionary;
	std::unordered_map<std::string, std::shared_ptr<ApertureMacro> > m_aperture_template_dictionary;
	bool m_file_complete;
};

#endif // _GRAPHICS_STATE_H
