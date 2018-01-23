#pragma once
#include "../shared.h"


namespace wot_stream::extension::utilities {

    //using namespace std;

    //enum class State {
    //    Started, Stopped
    //};

    //class State {
    //public:
    //    State();
    //    ~State();

    //    virtual std::size_t State::operator()(const State& state) const; // get hash

    //private:
    //    int id;
    //    function<bool(const State& current_state)> can_execute;
    //    function<void()> execute;
    //    unordered_set<int> asd;
    //};

    //std::size_t State::operator()(const State& state) const {
    //    return static_cast<std::size_t>(state.id);
    //}

    //// -----------------------

    //class FSM { // Configurable
    //public:
    //    FSM();
    //    ~FSM();

    //    void SwitchState(const State& new_state);
    //    void AddState(const State& new_state, function<void()> execute, function<bool(const State& current)> can_execute);

    //    void AddState(shared_ptr<State> state);


    //private:

    //    unordered_set<shared_ptr<State>> states;

    //    void ExitState();
    //    void EnterState(const State& new_state);



    //};

    //FSM::FSM() {}
    //FSM::~FSM() {}

    //void FSM::AddState(shared_ptr<State> state) { states.insert(state); }

    // ------------------------


}