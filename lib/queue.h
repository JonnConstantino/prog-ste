/*
 * Arquivo: adc.h
 * Autor: Arliones Hoeller
 * Organização: IFSC-SJE
 */

#ifndef __FIFO_H__
#define __FIFO_H__

template<int N, typename T>
class Fifo
{
public:
    Fifo() : in(0), out(0), size(0)
    {}
    ~Fifo() {}

    void enqueue(T obj)
    {
        if (size < N)
        {
            size++;
            data[in] = obj;
            in = (in + 1) % N;
        }
    }

    T dequeue()
    {
        if (size > 0)
        {
            size--;
            T aux = data[out];
            out = (out + 1) % N;
            return aux;
        }
    }

    int length()
    {
        return size;
    }

private:
    T data[N];
    int in, out, size;
};

#endif /* __FIFO_H__ */