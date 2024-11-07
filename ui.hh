#include <assert.h>
#include <raylib.h>
#include "data.hh"

template<int size>
class Button {
    float m_offset;
    Vector2 m_position;
    Sound_Record* m_rec;

  public:
    Button(float offset, Vector2 pos, Sound_Record* ptr) :
      m_offset(offset),
      m_position(pos),
      m_rec(ptr){};

    Color bg() const {
        return RAYWHITE;
    }

    void draw() const {
        assert(m_rec != nullptr);
        float width = (size - m_rec->width()) / 2;
        m_rec->draw(
            m_position.x + width + m_offset,
            m_position.y + width
        );
    }
};
