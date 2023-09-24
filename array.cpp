#include "array.h"

Array::Array(std::ostream &ostream) : Ostream_(ostream) {
    this->Capacity_ = 2;
    this->Size_ = 0;
    this->Elements_ = new int[this->Capacity_];

    Ostream_.clear();
    this->Ostream_ << "Constructed. " << (*this);
}

Array::Array(const Array &array) : Ostream_(array.Ostream_) {
    this->Capacity_ = array.Capacity();
    this->Size_ = array.Size();
    this->Elements_ = new int[this->Capacity_];

    for (size_t i = 0; i < this->Size_; ++i) {
        Elements_[i] = array[i];
    }

    Ostream_.clear();
    this->Ostream_ << "Constructed from another Array. " << (*this) << std::endl;
}

Array::Array(size_t size, std::ostream &ostream, int defaultValue) :
    Size_(size), Capacity_(size * 2), Ostream_(ostream) {
    this->Elements_ = new int[this->Capacity_];

    for (size_t i = 0; i < this->Size_; ++i) {
        this->Elements_[i] = defaultValue;
    }

    Ostream_.clear();
    this->Ostream_ << "Constructed with default. " << (*this) << std::endl;
}

Array::~Array() {
    delete[] this->Elements_;

    Ostream_.clear();
    this->Ostream_ << "Destructed " << this->Size_ << std::endl;
}


size_t Array::Size() const {
    return this->Size_;
}

size_t Array::Capacity() const {
    return this->Capacity_;
}

void Array::Reserve(size_t newCapacity) {
    if (newCapacity <= this->Capacity_) {
        return;
    }
    this->Capacity_ = newCapacity;

    int* new_elements = new int[this->Capacity_];
    for (size_t i = 0; i < this->Size_; ++i) {
        new_elements[i] = (*this)[i];
    }

    delete[] this->Elements_;
    this->Elements_ = new_elements;
}

void Array::Resize(size_t newSize) {
    if (newSize >= this->Capacity_) {
        this->Reserve(newSize);
    }
    if (newSize >= this->Size_) {
        for (size_t i = this->Size_; i < newSize; ++i) {
            (*this)[i] = 0;
        }
    }

    this->Size_ = newSize;
}

void Array::PushBack(int value)  {
    this->Elements_[this->Size_] = value;
    ++this->Size_;

    if (this->Size_ == this->Capacity_) {
        this->Reserve(this->Size_ * 2);
    }
}

void Array::PopBack() {
    --this->Size_;
}


const int& Array::operator [](const size_t i) const {
    return this->Elements_[i];
}

int& Array::operator [](const size_t i) {
    return this->Elements_[i];
}

Array::operator bool() const {
    return (this->Size_ > 0);
}


bool Array::operator <(const Array& it) const {
    for (size_t i = 0; i < std::min(this->Size_, it.Size()); ++i) {
        return (*this)[i] < it[i];
    }

    return (this->Size_ < it.Size());
}

bool Array::operator >(const Array& it) const {
    for (size_t i = 0; i < std::min(this->Size_, it.Size()); ++i) {
        return (*this)[i] > it[i];
    }

    return (this->Size_ > it.Size());
}

bool Array::operator !=(const Array& it) const {
    for (size_t i = 0; i < std::min(this->Size_, it.Size()); ++i) {
        return (*this)[i] != it[i];
    }

    return (this->Size_ != it.Size());
}

bool Array::operator ==(const Array& it) const {
    for (size_t i = 0; i < std::min(this->Size_, it.Size()); ++i) {
        return (*this)[i] == it[i];
    }

    return (this->Size_ == it.Size());
}

bool Array::operator <=(const Array& it) const {
    for (size_t i = 0; i < std::min(this->Size_, it.Size()); ++i) {
        return (*this)[i] <= it[i];
    }

    return (this->Size_ <= it.Size());
}

bool Array::operator >=(const Array& it) const {
    for (size_t i = 0; i < std::min(this->Size_, it.Size()); ++i) {
        return (*this)[i] >= it[i];
    }

    return (this->Size_ >= it.Size());
}


Array& Array::operator <<(const int& value) {
    this->PushBack(value);

    return *this;
}

Array& Array::operator <<(const Array& it) {
    this->Reserve((this->Size_ + it.Size()) * 2);

    for (size_t i = 0; i < it.Size(); ++i) {
        (*this)[this->Size_ + i] = it[i];
    }

    this->Size_ += it.Size();

    return *this;
}


std::ostream& operator <<(std::ostream& ostream, const Array& array) {
    ostream.clear();

    ostream << "Result Array's capacity is " << array.Capacity() << " and size is " << array.Size();

    if (array.Size() > 0) {
        ostream << ", elements are: " << array[0];
        for (size_t i = 1; i < array.Size(); ++i) {
            ostream << ", " << array[i];
        }
    }

    return ostream;
}

