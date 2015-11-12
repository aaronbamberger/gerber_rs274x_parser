#include "GraphicsState.hh"
#include "GerberClasses/UnitSpecifier.hh"
#include "GerberClasses/GlobalDefs.hh"
#include "GerberClasses/StepAndRepeat.hh"
#include "GerberClasses/LevelPolarity.hh"
#include "GerberClasses/Point.hh"
#include "GerberClasses/ApertureMacro.hh"
#include "GerberClasses/Aperture.hh"

#include <memory>
#include <unordered_map>

GraphicsState::GraphicsState() : m_coord_format(nullptr),
									m_unit_type(Gerber::UnitType::UNIT_TYPE_UNDEFINED),
									m_current_aperture(-1),
									m_current_quadrant_mode(Gerber::QuadrantMode::QUADRANT_MODE_UNDEFINED),
									m_current_interp_mode(Gerber::InterpolationMode::INTERPOLATION_MODE_UNDEFINED),
									m_current_point(0.0, 0.0),
									m_current_step_and_repeat(std::make_shared<StepAndRepeat>()),
									m_current_level_polarity(Gerber::LevelPolarityType::LEVEL_POLARITY_DARK),
									m_current_region_mode_state(Gerber::RegionModeState::REGION_MODE_OFF),
									m_file_complete(false)
{}

GraphicsState::~GraphicsState()
{}

const std::shared_ptr<FormatSpecifier>& GraphicsState::coord_format()
{
    return m_coord_format;
}

const Gerber::UnitType GraphicsState::unit_type()
{
    return m_unit_type;
}

const int GraphicsState::current_aperture()
{
    return m_current_aperture;
}

const Gerber::QuadrantMode GraphicsState::current_quadrant_mode()
{
    return m_current_quadrant_mode;
}

const Gerber::InterpolationMode GraphicsState::current_interp_mode()
{
    return m_current_interp_mode;
}

const Gerber::RegionModeState GraphicsState::current_region_mode_state()
{
    return m_current_region_mode_state;
}

const bool GraphicsState::file_complete()
{
    return m_file_complete;
}

bool GraphicsState::set_current_aperture(int aperture_num)
{
    // Attempt to update the current aperture.  It is only valid to switch to
    // an aperture that is already in the aperture dictionary, so if the requested
    // aperture id is missing from the aperture dictionary, the current aperture isn't
    // updated and the error is returned
    auto aperture = m_aperture_dictionary.find(aperture_num);
    if (aperture != m_aperture_dictionary.end()) {
        m_current_aperture = aperture_num;
        return true;
    } else {
        return false;
    }
}

bool GraphicsState::set_coord_format(std::shared_ptr<FormatSpecifier> coord_format)
{
	// Coordinate format can only be set once, so if it has already been set
	// it is an error to attempt to set it again
	if (m_coord_format) {
		return false;
	} else {
		m_coord_format = coord_format;
	}

	return true;
}

bool GraphicsState::set_unit_type(Gerber::UnitType unit_type) {
	// Unit type can only be set once, so if it has already been set
	// it is an error to attempt to set it again
	if (m_unit_type != Gerber::UnitType::UNIT_TYPE_UNDEFINED) {
		return false;
	} else {
		m_unit_type = unit_type;
	}

	return true;
}

bool GraphicsState::define_aperture(int aperture_num, std::shared_ptr<Aperture> aperture)
{
    // Attempt to add the new aperture definition to the aperture dictionary.
    // If the insertion fails, it means an aperture with this id has already
    // been inserted.  Multiple aperture definitions for the same id are prohibited
    // by the spec, so we leave the new aperture definition un-inserted, and return
    // the error
    return m_aperture_dictionary.insert(std::make_pair(aperture_num, aperture)).second;
}

bool GraphicsState::add_aperture_macro(std::shared_ptr<ApertureMacro> macro)
{
    // Attempt to add the aperture macro to the aperture template dictionary.
    // If the insertion fails, it means a macro with this name has already been inserted.
    // Multiple aperture macros with the same name are prohibited by the spec, so we leave
    // the aperture macro un-inserted and return the error
    return m_aperture_template_dictionary.insert(std::make_pair(macro->macro_name(), macro)).second;
}

bool GraphicsState::set_file_complete()
{
    // The file starts incomplete, and is set complete by seeing an end-of-file
    // command.  Only one end-of-file command is allowed per file, and it must
    // be the last command in the file.  If more than 1 end-of-file command exists
    // in the command stream, we return the error
    if (!m_file_complete) {
        m_file_complete = true;
        return true;
    } else {
        return false;
    }
}

bool GraphicsState::check_aperture_macro(std::string macro_name)
{
    auto macro = m_aperture_template_dictionary.find(macro_name);
    if (macro != m_aperture_template_dictionary.end()) {
        return true;
    } else {
        return false;
    }
}

const std::shared_ptr<ApertureMacro> GraphicsState::lookup_aperture_macro(std::string macro_name)
{
    return m_aperture_template_dictionary.at(macro_name);
}

void GraphicsState::set_interp_mode(Gerber::InterpolationMode mode)
{
    m_current_interp_mode = mode;
}

void GraphicsState::set_quadrant_mode(Gerber::QuadrantMode mode)
{
    m_current_quadrant_mode = mode;
}

void GraphicsState::set_region_mode_state(Gerber::RegionModeState state)
{
    m_current_region_mode_state = state;
}

void GraphicsState::set_step_and_repeat(std::shared_ptr<StepAndRepeat> step_and_repeat)
{
    m_current_step_and_repeat = step_and_repeat;
}

void GraphicsState::set_level_polarity(Gerber::LevelPolarityType level_polarity)
{
    m_current_level_polarity = level_polarity;
}
