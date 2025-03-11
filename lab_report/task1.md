# Task 1 Lab Report

## 1.任务目标

- 为ContentMessage中的结构体Header添加一个新的元数据：MessageType，用于区分消息类型，并修改相关函数。


## 2.实现思路

### 2.1 ContentMessage.hh

在ContentMessage.hh中添加

```c++
struct ContestMessage
{
  struct Header {
    /* Message types: 0 = data, 1 = ack */
    uint64_t message_type;
  }
};
```
考虑到ContentMessage的结构,直接在Header中添加一个标记的元数据更好,如果选择添加到ContentMessage中作为一个新的枚举类型,会导致ContentMessage的构造更复杂.

### 2.2 ContentMessage.cc

    修改了ContentMessage.cc中的各个函数

- Header的构造函数添加了message_type的初始化
```c++
    ContestMessage::Header::Header( const string & str )
    ContestMessage::Header::Header( const uint64_t s_sequence_number )
```
- to_string函数添加了message_type的输出
```c++
    string ContestMessage::Header::to_string() const
```
- transform_into_ack函数添加了message_type的赋值
```c++
    void ContestMessage::transform_into_ack(
        const uint64_t sequence_number,
        const uint64_t recv_timestamp 
    ){
        /* set the message type to 1 */
        header.message_type = 1;
    }
```
- is_ack函数修改为判断message_type是否为1
```c++
    bool ContestMessage::is_ack() const
{
  return header.message_type == 1;
}
```

### 2.3 receiver.cc

    receiver.cc中未修改

## 3 测试结果

    运行后无问题



