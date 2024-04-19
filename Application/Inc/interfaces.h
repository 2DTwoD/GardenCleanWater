#ifndef INTERFACES_H
#define INTERFACES_H

class ISwitch {
	public:
		virtual bool isActive() = 0;
};

class IUpdated {
	public:
		virtual void update() = 0;
};
#endif //INTERFACES_H