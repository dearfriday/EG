//
// Created by friday on 07/05/2019.
//

#pragma once


#include <tuple>

namespace eg {

    template<typename ...T>
    class future;

    template <typename ...T>
    class promise;


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


    private:

        template <do_now now>
        void do_set_value(std::tuple<T...> result){

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

        template <typename Func, typename Result>
        Result  then(Func &&ff){
            return then_impl(std::move(ff));
        }


    private:
        template <typename Func, typename Result>
        Result  then_impl(Func &&ff){

        }
    };


}