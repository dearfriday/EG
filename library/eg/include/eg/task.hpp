//
// Created by nova on 18/07/2019.
//


#include <eg/type.hpp>
namespace eg{



    struct task {
        virtual ~task() = 0;
        
        task(const task &) = delete;
        task& operator = (const task&) = delete;
    };


    template <typename Func>
    struct cb_task final : public  task{

    };


}