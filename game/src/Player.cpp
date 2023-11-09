#include "pch.h"
#include "player.h"
#include "glm/gtx/rotate_vector.hpp"
#include "engine/core/input.h"
#include "engine/key_codes.h"

player::player() : m_timer(0.0f), m_speed(5.0f)
{
	;
}

player::~player()
{
}

void player::initialise(engine::ref<engine::game_object> object)
{
	m_object = object;
	m_object->set_forward(glm::vec3(0.f, 0.f, -1.f));
	m_object->set_position(glm::vec3(0.f, 0.5, 10.f));
	m_object->animated_mesh()->set_default_animation(1);
}

void player::on_update(const engine::timestep& time_step)
{
	m_object->set_rotation_amount(atan2(m_object->forward().x, m_object->forward().z));

	// Start with no movement direction
	glm::vec3 movement_direction = glm::vec3(0.f);

	// Check for forward movement
	if (engine::input::key_pressed(engine::key_codes::KEY_W)) // Move forward
	{
		m_object->set_position(m_object->position() + glm::normalize(m_object->forward()) * m_speed * (float)time_step);
	}

	if (engine::input::key_pressed(engine::key_codes::KEY_S)) // Move back
	{
		m_object->set_position(m_object->position() - glm::normalize(m_object->forward()) * m_speed * (float)time_step);
	}

	//////// Check for left/right movement and update the forward vector accordingly
	if (engine::input::key_pressed(engine::key_codes::KEY_A)) // Move left
	{
		// Calculate the left direction vector for strafing
		glm::vec3 left_direction = -glm::normalize(glm::cross(m_object->forward(), m_object->up()));
		m_object->set_position(m_object->position() + left_direction * m_speed * (float)time_step);
	}

	if (engine::input::key_pressed(engine::key_codes::KEY_D)) // Move right
	{
		// Calculate the right direction vector for strafing
		glm::vec3 right_direction = glm::normalize(glm::cross(m_object->forward(), m_object->up()));
		m_object->set_position(m_object->position() + right_direction * m_speed * (float)time_step);
	}



	if (engine::input::key_pressed(engine::key_codes::KEY_Q)) // left
		turn(1.0f * time_step);
	else if (engine::input::key_pressed(engine::key_codes::KEY_E)) // right
		turn(-1.0f * time_step);
	else if (engine::input::key_pressed(engine::key_codes::KEY_SPACE)) // space
		jump();

	if (m_timer > 0.0f)
	{
		m_timer -= (float)time_step;
		if (m_timer < 0.0f)
		{
			m_object->animated_mesh()->switch_root_movement(false);
			m_object->animated_mesh()->switch_animation(m_object->animated_mesh()->default_animation());
			m_speed = 5.0f;
		}
	}

	m_object->animated_mesh()->on_update(time_step);
}

void player::turn(float angle)
{
	///// Rotate the forward vector around the Y-axis
	m_object->set_forward(glm::rotate(m_object->forward(), angle, glm::vec3(0.f, 1.f, 0.f)));

	// Recalculate the right vector based on the new forward vector
	m_object->set_right(glm::normalize(glm::cross(m_object->forward(), glm::vec3(0.f, 1.f, 0.f))));

	// The up vector should remain the same if you're only rotating around the Y-axis
}

void player::update_camera(engine::perspective_camera& camera)
{
	float A = 2.f;
	float B = 3.f;
	float C = 6.f;

	glm::vec3 cam_pos = m_object->position() - glm::normalize(m_object->forward()) * B;
	cam_pos.y += A;

	glm::vec3 cam_look_at = m_object->position() + glm::normalize(m_object->forward()) * C;
	cam_look_at.y = 0.f;
	camera.set_view_matrix(cam_pos, cam_look_at);
}

void player::jump()
{
	m_object->animated_mesh()->switch_root_movement(true);
	m_object->animated_mesh()->switch_animation(3);
	m_speed = 5.0f;
	m_timer = m_object->animated_mesh()->animations().at(3)->mDuration;
}


