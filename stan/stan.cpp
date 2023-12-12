#include <iostream>

// Context
class Context;

// State
class State {
public:
    virtual void handle(Context& context) const = 0;
};

// ConcreteStateA
class ConcreteStateA : public State {
public:
    void handle(Context& context) const override;
};

// ConcreteStateB
class ConcreteStateB : public State {
public:
    void handle(Context& context) const override;
};

// Context
class Context {
private:
    State* currentState;

public:
    Context(State* initialState) : currentState(initialState) {}

    void setState(State* newState) {
        currentState = newState;
    }

    void request() {
        currentState->handle(*this);
    }
};

// ConcreteStateA implementation
void ConcreteStateA::handle(Context& context) const {
    std::cout << "ConcreteStateA is handling the request." << std::endl;
    // Optionally, update the context's state
    context.setState(new ConcreteStateB());
}

// ConcreteStateB implementation
void ConcreteStateB::handle(Context& context) const {
    std::cout << "ConcreteStateB is handling the request." << std::endl;
    // Optionally, update the context's state
    context.setState(new ConcreteStateA());
}

int main() {
    ConcreteStateA initialState;
    Context context(&initialState);

    // The context is initially in ConcreteStateA
    context.request();

    // After the request, the context transitions to ConcreteStateB
    context.request();

    // The context can continue to handle requests, alternating between states
    context.request();
    context.request();

    return 0;
}
