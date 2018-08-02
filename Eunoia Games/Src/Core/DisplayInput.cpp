#include "DisplayInput.h"
#include <cstring>

namespace Eunoia { namespace Core {

	DisplayInput::DisplayInput()
	{
		memset(m_keys, false, INPUT_MAX_KEYS * sizeof(bool));
		memset(m_lastKeys, false, INPUT_MAX_KEYS * sizeof(bool));
		memset(m_buttons, false, INPUT_MAX_MOUSE_BUTTONS * sizeof(bool));
		memset(m_lastButtons, false, INPUT_MAX_MOUSE_BUTTONS * sizeof(bool));
	}

	void DisplayInput::Update()
	{
		memcpy(m_lastKeys, m_keys, INPUT_MAX_KEYS * sizeof(bool));
		memcpy(m_lastButtons, m_buttons, INPUT_MAX_MOUSE_BUTTONS * sizeof(bool));
	}

	void DisplayInput::SetKeyState(Key key, bool state)
	{
		m_keys[key] = state;
	}

	void DisplayInput::SetMouseButtonState(MouseButton button, bool state)
	{
		m_buttons[button] = state;
	}

	bool DisplayInput::IsKeyDown(Key key) const
	{
		return m_keys[key];
	}

	bool DisplayInput::IsKeyPressed(Key key) const
	{
		return m_keys[key] && !m_lastKeys[key];
	}

	bool DisplayInput::IsKeyReleased(Key key) const
	{
		return !m_keys[key] && m_lastKeys[key];
	}

	bool DisplayInput::IsMouseButtonDown(MouseButton button) const
	{
		return m_buttons[button];
	}

	bool DisplayInput::IsMouseButtonPressed(MouseButton button) const
	{
		return m_buttons[button] && !m_lastButtons[button];
	}

	bool DisplayInput::IsMouseButtonReleased(MouseButton button) const
	{
		return !m_buttons[button] && m_lastButtons[button];
	}

} }
