#pragma once

#include "Singleton.h"
#include "Messages.h"
#include <entt.hpp>


class MessageManager : public Singleton<MessageManager>
{
    entt::dispatcher dispatcher;
    
public:
    MessageManager() : dispatcher{} {}

    inline entt::dispatcher& GetDispatcher() noexcept { return dispatcher; }
    
    /*! connects to a specific event */
    template <typename E, typename Receiver>
    inline void subscribe(Receiver* receiver) noexcept
    {
        dispatcher.sink<E>().connect(receiver);
    }
    
    /*! disconnects from a specific event */
    template <class E, typename Receiver>
    inline void unsubscribe(Receiver* receiver) noexcept
    {
        dispatcher.sink<E>().disconnect(receiver);
    }
    
    /*! triggers an event of type E */
    template <typename E, typename ... Args>
    inline void emit(Args&& ... args) noexcept
    {
        dispatcher.trigger<E>(args ...);
    }

    /*! puts an event of type E into the queue but does not send it to listeners */
    template <typename E, typename ... Args>
    inline void enqueue(Args&& ... args) noexcept
    {
        dispatcher.enqueue<E>(args ...);
    }
    
    /*! send all queued events to their respective listeners */
    template <typename E, typename ... Args>
    inline void update(Args&& ... args) noexcept
    {
        dispatcher.update<E>(args ...);
    }
};
