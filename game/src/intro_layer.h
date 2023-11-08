#pragma once

#include "engine.h"

class introlayer : public engine::layer {
public:
    introlayer();
    ~introlayer();

    void on_update(const engine::timestep& time_step) override;
    void on_render() override;
    void on_event(engine::event& event) override;

private:
    // Text manager for rendering text
    std::shared_ptr<engine::text_manager> m_text_manager;
};

