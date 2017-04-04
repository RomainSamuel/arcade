#include "IGUI.hpp"

#include "IGUI.hpp"

namespace arcade
{
  class GUI : public IGUI
  {
    std::vector<IComponent *> _components;

  public:
    GUI();
    virtual ~GUI();

    virtual std::size_t size() const;
	  virtual IComponent const &operator[](std::size_t n) const;

	  virtual std::vector<IComponent *>::const_iterator begin() const;
	  virtual std::vector<IComponent *>::const_iterator end() const;
  };
}
