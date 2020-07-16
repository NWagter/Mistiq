#pragma once
//this Event system is heavily inspired by the following answer on StackOverflow
//https://stackoverflow.com/questions/23973914/c-like-delegates-in-c

template <typename FMember, typename Class, typename... Args>
class EventClassMemberCall {
	Class* m_Object;
	FMember(Class::* m_Member)(Args...);
public:
	EventClassMemberCall(Class* a_Object, FMember(Class::* a_Member)(Args...)) : m_Object(a_Object), m_Member(a_Member) {}

	FMember operator()(Args... a_Args) {
		return (m_Object->*m_Member)(std::forward<Args>(a_Args)...);
	}
};

template <typename Signature>
class Event;

template <typename... Args>
class Event<void(Args...)>
{
	struct EventCallBase
    {
		virtual ~EventCallBase() {}
		virtual void Execute(Args... a_Args) = 0;
	};

	template <typename T>
	struct EventCall : EventCallBase {
		template <typename S>
		EventCall(S&& a_Callback) : m_Callback(std::forward<S>(a_Callback)) {}

		void Execute(Args... a_Args) {
			return m_Callback(std::forward<Args>(a_Args)...);
		}

		T m_Callback;
	};

public:
	Event() {}

    //Adding functions to event
	template <typename T>
	Event& operator+= (T&& a_Callback) {
		m_Callbacks.emplace_back(new EventCall<T>(std::forward<T>(a_Callback)));
		return *this;
	}

    //Removing functions to event
	template <typename T>
	Event& operator-= (T&& a_Callback) {
		Call<T> tmp(std::forward<T>(a_Callback));
		auto it = std::find(m_Callbacks.begin(), m_Callbacks.end(), tmp);
		if(it != nullptr) m_Callbacks.erase(it);
		return *this;
	}

    //Execute all callback functions that are part of this event
	void operator()(Args... a_Args) {
		for (auto& callback : m_Callbacks) {
			callback->Execute(a_Args...);
		}
	}

public:
	std::vector<std::unique_ptr<EventCallBase>> m_Callbacks;
};

template <typename FMember, typename Class, typename... Args>
EventClassMemberCall<FMember, Class, Args...> MemFunc(Class& a_Object, FMember(Class::* a_Member)(Args...)) {
	return EventClassMemberCall<FMember, Class, Args...>(&a_Object, a_Member);
}
