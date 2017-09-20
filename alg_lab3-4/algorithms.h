#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <QVector>
#include <QTextStream>
#include <QObject>

#ifdef WIN32
#define ENDL "\r\n"
#else
#define ENDL "\n"
#endif

template<class T>
class Algorithms
{
public:
    static void shellSort(QVector<T> &array,
                     QTextStream *stream = nullptr);
    static void mergeSort(QVector<T> &array,
                     QTextStream *stream = nullptr);
};

template<class T>
void Algorithms<T>::shellSort(QVector<T> &array, QTextStream *stream)
{
    for(int step = array.size() / 2; step > 0; step /= 2)
    {
        if(stream)
            *stream << "Step = " << step << ENDL;
        for(int i = step; i < array.size(); ++i)
        {
            if(stream)
                *stream << "Holding element array[" << i
                        << "] = " << array.at(i) << ENDL;
            T temp = array.at(i);
            int j;
            for(j = i; j >= step && array.at(j - step) > temp; j -= step)
            {
                if(stream)
                    *stream << "Shifting elements array[" << j
                            << "] and array["<< j - step
                            << "]" << ENDL;
                array[j] = array[j - step];
            }

            if(stream)
                *stream << "Placing array[" << i
                         << "] element on its place at array["
                         << j << "]" << ENDL;
            array[j] = temp;
        }
    }
    if(stream)
        *stream << "Array sorted" << ENDL;
}

template<class T>
void Algorithms<T>::mergeSort(QVector<T> &array, QTextStream *stream)
{
    if(array.size() > 1)
    {
        if(stream)
            *stream << "Dividing array with size="
                    << array.size() << " to vectors with size="
                     << array.size() / 2 << " and size="
                     << array.size() / 2 + array.size() % 2 << ENDL;

        QVector<T> left_vector = array.mid(0, array.size() / 2);
        mergeSort(left_vector);
        QVector<T> right_vector = array.mid(array.size() / 2,
                                            array.size() / 2 + array.size() % 2);
        mergeSort(right_vector);

        if(stream)
            *stream << "Merging vectors with size="
                    << left_vector.size() << " and size="
                    << right_vector.size() << ENDL;
        for(int i = 0, left_index = 0, right_index = 0; i < array.size(); ++i)
        {
            array[i] = (left_index < left_vector.size()
                                && (right_index >= right_vector.size()
                                    || left_vector.at(left_index) < right_vector.at(right_index))
                                ? left_vector.at(left_index++) : right_vector.at(right_index++));
        }
    }
}


#endif // ALGORITHMS_H
