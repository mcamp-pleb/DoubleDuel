#include "TextBox.h"

TextBox::TextBox()
{
	
}

TextBox::~TextBox()
{

}

void TextBox::Init(SystemSettings *settings)
{
	m_tempstr = settings->machineName;
	
	m_textBox.setSize(sf::Vector2f(175.0f, 50.0f));
	m_textBox.setPosition(sf::Vector2f((settings->resWidth / 2.0f) - (m_textBox.getSize().x / 2.0f), 100.0f));
	m_textBox.setFillColor(sf::Color::White);

	m_textIn.setFont(settings->sfm_Font);
	m_textIn.setString(m_tempstr);
	m_textIn.setPosition(m_textBox.getPosition().x + 5.0f, m_textBox.getPosition().y + 5.0f);
	m_textIn.setFillColor(sf::Color::Black);
}

void TextBox::Draw(SystemSettings *settings)
{
	settings->sfm_window.draw(m_textBox);
	settings->sfm_window.draw(m_textIn);
}

void TextBox::HandleKey()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
	{
		//Remove Char from back of string
		if (m_tempstr.size() > 0)
		{
			m_tempstr.pop_back();
		}
	}

	//Add Char to back of string
	if (m_tempstr.size() < 8)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('A');
			}
			else
			{
				m_tempstr.push_back('a');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('B');
			}
			else
			{
				m_tempstr.push_back('b');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('C');
			}
			else
			{
				m_tempstr.push_back('c');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('D');
			}
			else
			{
				m_tempstr.push_back('d');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('E');
			}
			else
			{
				m_tempstr.push_back('e');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('F');
			}
			else
			{
				m_tempstr.push_back('f');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('G');
			}
			else
			{
				m_tempstr.push_back('g');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('H');
			}
			else
			{
				m_tempstr.push_back('h');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('I');
			}
			else
			{
				m_tempstr.push_back('i');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('J');
			}
			else
			{
				m_tempstr.push_back('j');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('K');
			}
			else
			{
				m_tempstr.push_back('k');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('L');
			}
			else
			{
				m_tempstr.push_back('l');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('M');
			}
			else
			{
				m_tempstr.push_back('m');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('N');
			}
			else
			{
				m_tempstr.push_back('n');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('O');
			}
			else
			{
				m_tempstr.push_back('o');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('P');
			}
			else
			{
				m_tempstr.push_back('p');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('Q');
			}
			else
			{
				m_tempstr.push_back('q');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('R');
			}
			else
			{
				m_tempstr.push_back('r');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('S');
			}
			else
			{
				m_tempstr.push_back('s');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('T');
			}
			else
			{
				m_tempstr.push_back('t');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('U');
			}
			else
			{
				m_tempstr.push_back('u');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('V');
			}
			else
			{
				m_tempstr.push_back('v');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('W');
			}
			else
			{
				m_tempstr.push_back('w');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('X');
			}
			else
			{
				m_tempstr.push_back('x');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('Y');
			}
			else
			{
				m_tempstr.push_back('y');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('Z');
			}
			else
			{
				m_tempstr.push_back('z');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSlash))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('|');
			}
			else
			{
				m_tempstr.push_back('\\');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Comma))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('<');
			}
			else
			{
				m_tempstr.push_back(',');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('_');
			}
			else
			{
				m_tempstr.push_back('-');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Slash))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('?');
			}
			else
			{
				m_tempstr.push_back('/');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('+');
			}
			else
			{
				m_tempstr.push_back('=');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LBracket))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('{');
			}
			else
			{
				m_tempstr.push_back('[');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::RBracket))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('}');
			}
			else
			{
				m_tempstr.push_back(']');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Period))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('>');
			}
			else
			{
				m_tempstr.push_back('.');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Quote))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('"');
			}
			else
			{
				m_tempstr.push_back('\'');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::SemiColon))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back(':');
			}
			else
			{
				m_tempstr.push_back(';');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('!');
			}
			else
			{
				m_tempstr.push_back('1');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('@');
			}
			else
			{
				m_tempstr.push_back('2');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('#');
			}
			else
			{
				m_tempstr.push_back('3');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('$');
			}
			else
			{
				m_tempstr.push_back('4');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('%');
			}
			else
			{
				m_tempstr.push_back('5');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('^');
			}
			else
			{
				m_tempstr.push_back('6');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('&');
			}
			else
			{
				m_tempstr.push_back('7');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('*');
			}
			else
			{
				m_tempstr.push_back('8');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back('(');
			}
			else
			{
				m_tempstr.push_back('9');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				m_tempstr.push_back(')');
			}
			else
			{
				m_tempstr.push_back('0');
			}
		}
	}

	//Update String
	m_textIn.setString(m_tempstr);

}

void TextBox::ApplyName(SystemSettings *settings)
{
	settings->machineName = m_tempstr;
}