//
// Created by friday on 07/05/2019.
//

#pragma once


#include <tuple>
#include <assert.h>

namespace eg {

    template<typename ...T>
    class future;

    template <typename ...T>
    class promise;


    struct make_ready_future{};

    namespace internal {

        template<typename T>
        struct wrap_value_base {
            union any {
                any() noexcept {};
                ~any() {};

                T _value;
            };

            any _v;

            void set_wrap_value(T t) {

                new(&_v._value) T(t);
            }

            T &get_wrap_value() {
                return _v._value;
            }

            const T &get_wrap_value() const {
                return _v._value;
            }
        };


    }


    template <typename T>
    class pack_future{
    public:
        typedef future<T>   type;
        typedef promise<T>  promise_type;
        typedef std::tuple<T>  value_type;

//        template <typename Func, typename ...ARGS>
//        static type packed(Func &&ff, ARGS ...args){
//
//            return future<std::tuple<ARGS...>>();
//        }


        template <typename Func, typename ...ARGS>
        static type packed(Func &&ff, std::tuple<ARGS...> &&args){
            return future<T>(make_ready_future(), ff(args));
        }


    };

    template <typename T>
    using pack_future_t = typename pack_future<T>::type;



    struct future_state_base {

        enum class state : uint8_t {
            invalid = 0,
            future,
            result,
            exception
        };

        union any{
            any() { _state = state::future; }
            any(any &&a){
                //TODO exception ?
            }
            ~any(){}

            state _state;
            std::exception_ptr _ex;
        };
        any     _value;

        future_state_base() noexcept {};
        future_state_base(future_state_base &&f):_value(std::move(f._value)){}

        void set_exception(const std::exception_ptr &ex){
            new (&_value._ex) std::exception_ptr(ex);
        }


    };


    template<typename ...T>
    class future_state : public future_state_base, private internal::wrap_value_base<std::tuple<T...>> {
    public:
        future_state() noexcept {}
        future_state(future_state &&f) :future_state_base(std::move(f)) {
            if(_value._state == state::result){
                this->set_wrap_value(std::move(f.get_wrap_value()));
                f.get_wrap_value().~tuple();
            }
        }

        template <typename ...ARGS>
        void set(ARGS&& ...args){
//            assert(_value._state == state::future);
            this->set_wrap_value(args...);
            _value._state = state::result;
        }

        template <typename ...ARGS>
        void set(std::tuple<ARGS...> &&value){
//            assert(_value._state == state::future);
            this->set_wrap_value(std::tuple<ARGS...>(value));
            _value._state = state::result;
        }

        std::tuple<T...> get_value() &&{
//            assert(_value._state == state::result);
            return std::move(this->get_wrap_value());
        }



    };


    template<typename ...T>
    class promise {
        enum class do_now{no , yes};


        future<T...> *_future = nullptr;
        future_state<T...> _local_state;
        future_state<T...> *_state;
    public:
        promise() noexcept : _state(&_local_state) {}
        promise(promise &&p) noexcept:_future(p._future), _state(p._state){

        }
        promise(const promise &) = delete;





        future<T...> get_future() noexcept{
            assert(!_future && _state);
            return future<T...>(this);
        }

        ~promise() noexcept{}

        void set_value(const std::tuple<T...> &result) {
            do_set_value<do_now::no>(result);
        }

        void set_value(T &&... args){
            do_set_value<do_now::no>(args...);
        }


    private:


        template <do_now now>
        void do_set_value(std::tuple<T...> result){
            _state->set(result);

        }

        template <do_now now>
        void do_set_value(T&&... result){
            _state->set(result...);
            assert(_future != nullptr);
        }

        template<typename ...U>
        friend class future;


    };


    template<typename ...T>
    class future {
        promise<T...>* _promise;
        future_state<T...> _state;
    public:
        future(promise<T...> *pt):_promise(pt), _state(std::move(pt->_local_state)){
            _promise->_future = this;
            _promise->_state = &_state;
        }

        template <typename ...ARGS>
        future(make_ready_future, ARGS ...args){
            _state.set(args...);
        }

        future_state<T...> get_avaliable_state(){
            return std::move(_state);
        }


        template <typename Func, typename Result = pack_future_t<std::result_of_t<Func(T...)>> >
        Result  then(Func &&ff){
            return then_impl(std::move(ff));
        }


    private:
        future_state<T...> get_available_state() {
            if(_promise){
                //TODO exchange?
            }
            return std::move(_state);
        }



        template <typename Func, typename Result = pack_future_t<std::result_of_t<Func(T...)>> >
        Result  then_impl(Func &&ff){
            return pack_future<std::result_of_t<Func(T...)>>::packed(ff, get_available_state().get_value());
        }
    };


}