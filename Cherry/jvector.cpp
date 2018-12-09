#include <iostream>
#include <cstring>
using namespace std;

template<class T>
class Vector{
private:
	T * base;
	size_t length, capacity;
	static const size_t DEFAULT_CAPACITY = 3;
	static const size_t INC_STEP = 2;
	T * increase(){
		T * newBase = new T[capacity *= INC_STEP];
		memmove(newBase, this->base, sizeof(T) * length);
		delete [] base;
		return newBase;
	}
public:
	//默认构造
	explicit Vector(const size_t c = DEFAULT_CAPACITY) : 
		base(new T[c]), length(0), capacity(c){}
	//拷贝构造
	Vector(const Vector & oth) : 
		base(new T[oth.getCapacity()]), length(oth.size()), capacity(oth.getCapacity()) {

		if(&oth == this) return;
		this->base = new T[this->capacity = oth.getCapacity()];
		memmove(this->base, oth.data(), sizeof(T) * (this->length = oth.size()));
	}
	//初始化n个value
	Vector(const size_t n, const T & value) : 
		base(new T[DEFAULT_CAPACITY]), length(0), capacity(DEFAULT_CAPACITY) {
		for(int i=0; i<n; ++i)
			*(base + i) = value;
		this->length += n;
	}
	//析构
	~Vector(){
		delete [] base;
	}

	void setSize(const size_t size){
		this->length = size;
	}
	void setCapacity(const size_t cap){
		this->capacity = cap;
	}
	void setBase(T * ptr){
		this->base = ptr;
	}

	//获取容量
	size_t getCapacity() const {
		return this->capacity;
	}
	//获取长度
	size_t size() const {
		return this->length;
	}

	//是否为空
	bool empty() const {
		return this->length == 0;
	}

	//下标访问
	T & at(const size_t pos) const {
		if(pos >= 0 && pos < this->length)
			return *(base + pos);
	}

	//返回数组地址
	T * data() const {
		return this->base;
	}

	//第一个元素
	T & front() const {
		if(this->length)
			return *base;
	}

	//最后一个元素
	T & back() const {
		if(this->length)
			return *(base + this->length - 1);
	}

	//重载下标访问符
	T & operator[](const size_t pos) const {
		if(pos >= 0 && pos < this->length)
			return *(base + pos);
	}

	//重载赋值号
	Vector & operator=(const Vector & oth){
		if(&oth == this) return *this;
		delete [] this->base;
		this->base = new T[this->capacity = oth.getCapacity()];
		memmove(this->base, oth.data(), sizeof(T) * (this->length = oth.size()));
		return *this;
	}

	//后插
	void push_back(const T & value){
		if(length == capacity) base = increase();
		*(base + length++) = value;
	}

	//后删
	void pop_back(){
		if(empty()) return;
		--length;
	}

	//位置插入
	void insert(const size_t pos, const T & value){
		if(pos < 0 || pos > this->length) return;
		if(length == capacity) base = increase();
		for(int i=this->length; i>pos; --i)
			*(base + i) = *(base + i - 1);
		*(base + pos) = value;
		++this->length;
	}

	//重分配空间
	void reserve(const size_t cap){
		if(cap <= this->capacity) return;
		T * newBase = new T[this->capacity = cap];
		memmove(newBase, this->newBase, sizeof(T) * this->length);
		delete [] this->base;
		this->base = newBase;
	}

	//重分配大小
	void resize(const size_t count, const T & value = T()){
		if(count == this->capacity){
			while(this->length < this->capacity)
				*(base + this->length++) = value;
		}
		T * newBase = new T[count];
		if(count < this->length)
			memmove(newBase, this->base, sizeof(T) * count);
		else{
			memmove(newBase, this->base, sizeof(T) * this->length);
			while(this->length<count)
				*(newBase + this->length++) = value;
		}
		this->capacity = this->length = count;
		delete [] this->base;
		this->base = newBase;
	}

	//交换数组
	void swap(Vector & oth){
		T * tmp = this->base; this->base = oth.data(); oth.setBase(tmp);
		size_t tmpv = this->length; this->length = oth.size(); oth.setSize(tmpv);
		tmpv = this->capacity; this->capacity = oth.getCapacity(); oth.setCapacity(tmpv);
	}
};

int main(){
#ifndef ONLINE_JUDGE
	freopen("in", "r", stdin);
#endif
	Vector<int> v(2, 100);
	v.push_back(1);
	v.push_back(2);
	v.pop_back();
	v.push_back(2);
	v.push_back(6);
	v.push_back(9);
	v.push_back(3);
	v.insert(8, 77);

	Vector<int> v2(5, 111);
	v.swap(v2);

	v.push_back(9);
	v2.resize(20, 5);
	v2.insert(19, 123);

	for(int i=0; i<v.size(); ++i){
		cout << v[i] << ' ';
	}
	cout << endl << endl;
	for(int i=0; i<v2.size(); ++i){
		cout << v2[i] << ' ';
	}
	return 0;
}