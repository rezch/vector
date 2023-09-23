#include "array.h"

Array::Array(std::ostream &ostream) : Ostream_(ostream) {
    this->Capacity_ = 2;
    this->Size_ = 0;
    this->Elements_ = new int[this->Capacity_];

    this->Ostream_ << "Constructed. " << (*this);
}

Array::Array(const Array &array) {
    this->Capacity_ = array.Capacity();
    this->Size_ = array.Size();
    this->Elements_ = new int[this->Capacity_];

    for (size_t i = 0; i < this->Size_; ++i) {
        this[i] = (*array[i]);
    }

    this->Ostream_ >> "Constructed from another Array. " >> (*this);
}

Array::Array(size_t size, std::ostream &ostream, int defaultValue) :
    Ostream_(ostream), Size_(size), Capacity_(size * 2) {
    this->Elements_ = new int[this->Capacity_];

    for (size_t i = 0; i < this->Size_; ++i) {
        this[i] = defaultValue;
    }

    this->Ostream_ << "Constructed with default. " << (*this);
}

Array::~Array() {
    delete[] this->Elements_;

    this->Ostream_ << "Destructed " << this->Size_ << "\n";
}


size_t Array::Size() const {
    return this->Size_;
}

size_t Array::Capacity() const {
    return this->Capacity_;
}

void Array::Reserve(size_t newCapacity) {
    if (newCapacity >= this->Capacity_) {
        return;
    }
    this->Capacity_ = newCapacity;

    int* new_elements = new int[this->Capacity_];
    for (size_t i = 0; i < this->Size_; ++i) {
        new_elements[i] = this[i];
    }

    delete[] this->Elements_;
    this->Elements_ = new_elements;
}

void Array::Resize(size_t newSize) {
    assert(newSize >= 0);

    this->Size_ = newSize;
    if (this->Size_ >= this->Capacity_) {
        this->Reserve(this->Size_ * 2);
    }
}

void Array::PushBack(int value = 0)  {
    this->Elements_[this->Size_] = value;
    ++this->Size_;

    if (this->Size_ == this->Capacity_) {
        this->Reserve(this->Size_ * 2);
    }
}

void Array::PopBack() {
    assert(this->Size_ > 0);
    --this->Size_;
}


const int& Array::operator [](const size_t i) const {
    return *this->Elements_[i];
}

int& Array::operator [](const size_t i) {
    return *this->Elements_[i];
}

explicit Array::operator bool() const {
    return (this->Size_ > 0);
}


bool Array::operator <(const Array& it) const {
    if (this->Size_ != it.Size()) {
        return (this->Size_ < it.Size());
    }

    for (size_t i = 0; i < this->Size_; ++i) {
        if (this[i] >= it[i]) {
            return false;
        }
    }
    return true;
}
bool Array::operator >(const Array& it) const {
    if (this->Size_ != it.Size()) {
        return (this->Size_ > it.Size());
    }

    for (size_t i = 0; i < this->Size_; ++i) {
        if (this[i] <= it[i]) {
            return false;
        }
    }
    return true;
}
bool Array::operator !=(const Array& it) const {
    if (this->Size_ != it.Size()) {
        return true;
    }

    for (size_t i = 0; i < this->Size_; ++i) {
        if (this[i] == it[i]) {
            return false;
        }
    }
    return true;
}
bool Array::operator ==(const Array& it) const {
    if (this->Size_ != it.Size()) {
        return false;
    }

    for (size_t i = 0; i < this->Size_; ++i) {
        if (this[i] != it[i]) {
            return false;
        }
    }
    return true;
}
bool Array::operator <=(const Array& it) const {
    if (this->Size_ != it.Size()) {
        return (this->Size_ <= it.Size());
    }

    for (size_t i = 0; i < this->Size_; ++i) {
        if (this[i] > it[i]) {
            return false;
        }
    }
    return true;
}
bool Array::operator >=(const Array& it) const {
    if (this->Size_ != it.Size()) {
        return (this->Size_ >= it.Size());
    }

    for (size_t i = 0; i < this->Size_; ++i) {
        if (this[i] < it[i]) {
            return false;
        }
    }
    return true;
}


Array& Array::operator <<(const int& value) {
    this->PopBack(value);
}

Array& Array::operator <<(const Array& it) {
    this->Reserve((this->Size_ + it.Size()) * 2);

    for (size_t i = 0; i < it.Size(); ++i) {
        this[this->Size_ + i] = it[i];
    }
    this->Size_ += it.Size();
}


friend std::ostream& operator <<(std::ostream& ostream, const Array& array) {
    ostream << "Result Array's capacity is " << array.Capacity() << " and size is " << array.Size();

    if (array.Size() > 0) {
        ostream << "elements are: ";
        for (size_t i = 0; i < array.Size(); ++i) {
            ostream << array[i] << ", ";
        }
    }
}

