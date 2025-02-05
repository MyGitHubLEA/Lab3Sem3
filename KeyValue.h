#pragma once

template <class Key, class Value>
struct KeyValue
{
    Key key = Key();
    Value value = Value();
    KeyValue(const Key& k, const Value& v) : key(k), value(v) {}
    KeyValue() {};
};

template <class Key, class Value>
std::ostream& operator << (std::ostream& out, const KeyValue<Key, Value>& kv)
{
    out << kv.key<<"   " << kv.value<< std::endl;
    return out;
}

