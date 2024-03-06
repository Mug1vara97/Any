#ifndef ANY_H
#define ANY_H

#include <memory>
#include <typeinfo>

class Any {
public:
    Any() : data(nullptr) {}
    
    template<typename T>
    Any(const T& value) : data(new ValueHolder<T>(value)) {}
    
    Any(const Any& other) : data(other.data ? other.data->clone() : nullptr) {}
    
    Any& operator=(Any other) {
        other.swap(*this);
        return *this;
    }
    
    bool Empty() const {
        return !data;
    }
    
    template<typename T>
    T GetValue() const {
        if (data && data->type() == typeid(T)) {
            return static_cast<ValueHolder<T>*>(data.get())->value;
        } else {
            throw std::bad_cast();
        }
    }
    
    void Clear() {
        data.reset();
    }
    
    ~Any() {
        Clear();
    }
    
private:
    struct BaseValueHolder {
        virtual ~BaseValueHolder() {}
        virtual const std::type_info& type() const = 0;
        virtual std::unique_ptr<BaseValueHolder> clone() const = 0;
    };
    
    template<typename T>
    struct ValueHolder : BaseValueHolder {
        T value;
        
        ValueHolder(const T& value) : value(value) {}
        
        const std::type_info& type() const override {
            return typeid(T);
        }
        
        std::unique_ptr<BaseValueHolder> clone() const override {
            return std::unique_ptr<BaseValueHolder>(new ValueHolder<T>(value));
        }
    };
    
    std::unique_ptr<BaseValueHolder> data;
    
    void swap(Any& other) {
        data.swap(other.data);
    }
};

#endif