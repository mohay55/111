#include "intro_layer.h"
#include <engine/events/key_event.h>
#include "example_layer.h"


introlayer::introlayer() : layer("introlayer") {
	auto text_shader = engine::renderer::shaders_library()->get("text_2D");

	// set color texture unit

	std::dynamic_pointer_cast<engine::gl_shader>(text_shader)->bind();
	std::dynamic_pointer_cast<engine::gl_shader>(text_shader)->set_uniform("projection",
		glm::ortho(0.f, (float)engine::application::window().width(), 0.f,
			(float)engine::application::window().height()));
    m_text_manager = engine::text_manager::create();
}

introlayer::~introlayer() {
    // Destructor code here
}

void introlayer::on_update(const engine::timestep& time_step) {
    // Update code here, if any

    // Begin scene
}

void introlayer::on_render() {

    engine::render_command::clear_color({ 0.1f, 0.1f, 0.1f, 1 });
    engine::render_command::clear();

    const auto text_shader = engine::renderer::shaders_library()->get("text_2D");
    m_text_manager->render_text(text_shader, "Welcome to the Game!", 10.f, (float)engine::application::window().height() - 25.f, 0.5f, glm::vec4(1.f, 1.f, 1.f, 1.f));
    m_text_manager->render_text(text_shader, "Press Enter to begin", 10.f, (float)engine::application::window().height() - 50.f, 0.5f, glm::vec4(1.f, 1.f, 1.f, 1.f));
}

void introlayer::on_event(engine::event& event)
{
    if (event.event_type() == engine::event_type_e::key_pressed)
    {
        auto& e = dynamic_cast<engine::key_pressed_event&>(event);
        if (e.key_code() == engine::key_codes::KEY_ENTER)
        {
            engine::render_command::toggle_wireframe();
        }
    }
}
