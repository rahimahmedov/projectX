//
// Created by Rahim Ahmedov on 27.02.23.
//

#ifndef PROJECTX_STATES_H
#define PROJECTX_STATES_H

namespace raft {


    class State {
    public:
        virtual void enter() = 0;
        virtual void exit() = 0;
        virtual State* timeout() = 0;
        virtual State* toggle() = 0;
    };

    class FollowerState: public State {

    };

    class CandidateState: public State {

    };

    class LeaderState: public State {

    };

    class ServerState {
    private:
        State* state;
    };

}


#endif //PROJECTX_STATES_H
