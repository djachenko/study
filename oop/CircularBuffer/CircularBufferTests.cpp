#include <stdio.h>
#include <stdlib.h>

#include "gtest/include/gtest/gtest.h"
#include "CircularBuffer.h"
#include "CircularBuffer.cpp"

TEST(Constructor,default)
{
	CircularBuffer<int> a;

	EXPECT_EQ(a.size(),0);
};


TEST(Constructor,copy)
{
	CircularBuffer<int> a(5,7);
	CircularBuffer<int> b=a;
	
	EXPECT_EQ(b.size(),a.size());

	for (int i=a.size(); i; i--)
	{
		EXPECT_EQ(a[i],b[i]);
	}
};

TEST(Constructor,size)
{
	CircularBuffer<int> a(5);

	EXPECT_EQ(a.size(),0);
	EXPECT_EQ(a.reserve(),5);
};

TEST(Constructor,filling)
{
	CircularBuffer<double> a(5,3.14);

	for (int i=0; i<5; i++)
	{
		EXPECT_EQ(a.at(i),3.14);
	}
}

TEST(OperatorBraces,default)
{
	int a[]={7,5,2,0,6,8};

	CircularBuffer<int> b(6);

	for (int i=0; i<6; i++)
	{
		b[i]=a[i];
	}

	for (int i=0; i<6; i++)
	{
		EXPECT_EQ(b[i],a[i]);
	}

	EXPECT_NO_THROW(b[-1]);
	EXPECT_NO_THROW(b[7]);
}

TEST(OperatorAt,default)
{
	int a[]={7,5,2,0,6,8};

	CircularBuffer<int> b(6);

	for (int i=0;i<6;i++)
	{
		b.push_back(a[i]);
	}

	for (int i=0; i<6; i++)
	{
		EXPECT_EQ(b.at(i),a[i]);
	}

	EXPECT_THROW(b.at(-1),CircularBufferException);
	EXPECT_THROW(b.at(6),CircularBufferException);
}

TEST(front,default)
{
	int a[]={7,5,2,0,6,8};

	CircularBuffer<int> b(6);

	EXPECT_THROW(b.front(), CircularBufferException);

	for (int i=0;i<6;i++)
	{
		b.push_back(a[i]);
	}

	for (int i=0; i<6; i++)
	{
		EXPECT_EQ(b.front(),a[i]);

		b.pop_front();
	}

	EXPECT_THROW(b.front(), CircularBufferException);
}

TEST(back,default)
{
	int a[]={7,5,2,0,6,8};

	CircularBuffer<int> b(6);

	EXPECT_THROW(b.back(),CircularBufferException);

	for (int i=0;i<6;i++)
	{
		b.push_back(a[i]);
	}

	for (int i=5; i>=0; i--)
	{
		EXPECT_EQ(b.back(),a[i]);

		b.pop_back();
	}

	EXPECT_THROW(b.back(),CircularBufferException);
}

TEST(linearize,default)
{
	int a[]={7,5,2,3,6,8};

	CircularBuffer<int> b(4);

	for (int i=0;i<5;i++)
	{
		b.push_back(a[i]);
	}

	EXPECT_EQ(b.is_linearized(),false);

	b.linearize();

	EXPECT_EQ(b[0],*(b.linearize()));
//	EXPECT_EQ(*(b.buffer),b[0]);

	EXPECT_EQ(b.is_linearized(),true);
}

TEST(rotate,default)
{
	int a[]={7,5,2,3,6,8};

	CircularBuffer<int> b(4);

	for (int i=0;i<5;i++)
	{
		b.push_back(a[i]);
	}

	for (int k=0; k<4; k++)
	{
		for (int i=0; i<4; i++)
		{
			for (int j=0; j<4; j++)
			{
				EXPECT_EQ(b[j],a[1+(j+i*k)%4]);
			}

			b.rotate(k);
		}
	}

	EXPECT_THROW(b.rotate(9), CircularBufferException);
	EXPECT_THROW(b.rotate(-15), CircularBufferException);
	
	CircularBuffer<int> c;

	EXPECT_THROW(c.rotate(2),CircularBufferException);
}

TEST(size,default)
{
	int a[]={7,5,2,3,6,8};

	CircularBuffer<int> b(4);

	EXPECT_EQ(b.size(),0);

	for (int i=0;i<4;i++)
	{
		b.push_back(a[i]);

		EXPECT_EQ(b.size(),i+1);
	}
	
	for (int i=4; i<6; i++)
	{
		b.push_back(a[i]);

		EXPECT_EQ(b.size(),4);
	}

	CircularBuffer<int> c;

	EXPECT_EQ(c.size(),0);

	CircularBuffer<int> d(6,7);

	EXPECT_EQ(d.size(),6);
}

TEST(empty,default)
{
	int a[]={7,5,2,3,6,8};

	CircularBuffer<int> b(4);

	EXPECT_EQ(b.empty(),true);

	for (int i=0;i<6;i++)
	{
		b.push_back(a[i]);

		EXPECT_EQ(b.empty(),false);
	}

	b.clear();

	EXPECT_EQ(b.empty(),true);

	CircularBuffer<int> c;

	EXPECT_EQ(c.empty(),true);

	CircularBuffer<int> d(6,5);

	EXPECT_EQ(d.empty(),false);
}

TEST(full,default)
{
	int a[]={7,5,2,3,6,8};

	CircularBuffer<int> b(4);

	EXPECT_EQ(b.full(),false);

	for (int i=0;i<3;i++)
	{
		b.push_back(a[i]);

		EXPECT_EQ(b.full(),false);
	}

	for (int i=3;i<6;i++)
	{
		b.push_back(a[i]);

		EXPECT_EQ(b.full(),true);
	}

	b.clear();

	EXPECT_EQ(b.full(),false);

	CircularBuffer<int> c;

	EXPECT_EQ(c.full(),false);

	CircularBuffer<int> d(6,5);

	EXPECT_EQ(d.full(),true);
}

TEST(reserve,default)
{
	int a[]={7,5,2,3,6,8};

	CircularBuffer<int> b(4);

	EXPECT_EQ(b.reserve(),4);

	for (int i=0;i<4;i++)
	{
		b.push_back(a[i]);

		EXPECT_EQ(b.reserve(),3-i);
	}

	for (int i=4;i<6;i++)
	{
		b.push_back(a[i]);

		EXPECT_EQ(b.reserve(),0);
	}

	b.clear();

	EXPECT_EQ(b.reserve(),4);

	CircularBuffer<int> c;
	
	EXPECT_EQ(c.reserve(),0);

	CircularBuffer<int> d(6,5);

	EXPECT_EQ(d.reserve(),0);
}

TEST(capacity,default)
{
	int a[]={7,5,2,3,6,8};

	CircularBuffer<int> b(4);

	EXPECT_EQ(b.capacity(),4);

	for (int i=0;i<4;i++)
	{
		b.push_back(a[i]);

		EXPECT_EQ(b.capacity(),4);
	}

	for (int i=4;i<6;i++)
	{
		b.push_back(a[i]);

		EXPECT_EQ(b.capacity(),4);
	}

	b.clear();

	EXPECT_EQ(b.capacity(),4);

	CircularBuffer<int> c;
	
	EXPECT_EQ(c.capacity(),0);

	CircularBuffer<int> d(6,5);

	EXPECT_EQ(d.capacity(),6);
}

TEST(set_capacity,default)
{
	int a[]={7,5,2,3,6,8};

	CircularBuffer<int> b(4);

	for (int i=0; i<4; i++)
	{
		b.push_back(a[i]);
	}

	for (int i=0; i<4; i++)
	{
		EXPECT_EQ(b.at(i),a[i]);
	}

	EXPECT_EQ(b.capacity(),4);

	b.set_capacity(6);

	EXPECT_EQ(b.capacity(),6);

	for (int i=0; i<4; i++)
	{
		EXPECT_EQ(b.at(i),a[i]);
	}

	for (int i=4; i<6; i++)
	{
		EXPECT_THROW(b.at(i),CircularBufferException);
	}

	EXPECT_EQ(b.is_linearized(),true);
	EXPECT_EQ(b.size(),4);

	b.set_capacity(3);

	EXPECT_EQ(b.capacity(),3);
	
	for (int i=0; i<3; i++)
	{
		EXPECT_EQ(b.at(i),a[i]);
	}

	for (int i=3; i<6; i++)
	{
		EXPECT_THROW(b.at(i),CircularBufferException);
	}

	EXPECT_EQ(b.is_linearized(),true);
	EXPECT_EQ(b.size(),3);
}

TEST(resize,default)
{
	int a[]={7,5,2,3,6,8};

	CircularBuffer<int> b(4);

	for (int i=0; i<4; i++)
	{
		b.push_back(a[i]);
	}

	for (int i=0; i<4; i++)
	{
		EXPECT_EQ(b.at(i),a[i]);
	}

	EXPECT_EQ(b.capacity(),4);

	b.resize(6,117);

	EXPECT_EQ(b.capacity(),6);
	EXPECT_EQ(b.reserve(),0);

	for (int i=0; i<4; i++)
	{
		EXPECT_EQ(b.at(i),a[i]);
	}

	for (int i=4; i<6; i++)
	{
		EXPECT_EQ(b.at(i),117);
	}

	EXPECT_EQ(b.is_linearized(),true);
	EXPECT_EQ(b.size(),6);

	b.resize(3,209);

	EXPECT_EQ(b.capacity(),3);
	
	for (int i=0; i<3; i++)
	{
		EXPECT_EQ(b.at(i),a[i]);
	}

	for (int i=3; i<6; i++)
	{
		EXPECT_THROW(b.at(i),CircularBufferException);
	}

	EXPECT_EQ(b.is_linearized(),true);
	EXPECT_EQ(b.size(),3);
}

TEST(OperatorIs,default)
{
	int a[]={7,5,2,3,6,8};

	CircularBuffer<int> b(4);

	for (int i=0; i<6; i++)
	{
		b.push_back(a[i]);
	}

	CircularBuffer<int> c(5,117);

	EXPECT_EQ(c.size(),5);
	EXPECT_EQ(c.capacity(),5);
	EXPECT_EQ(c.is_linearized(),true);

	for (int i=0; i<5; i++)
	{
		EXPECT_EQ(c.at(i),117);
	}

	c=b;
	
	EXPECT_EQ(c.size(),b.size());
	EXPECT_EQ(c.capacity(),b.capacity());
	EXPECT_EQ(c.is_linearized(),b.is_linearized());

	for (int i=0; i<4; i++)
	{
		EXPECT_EQ(c.at(i),b.at(i));
	}

	EXPECT_THROW(c.at(4),CircularBufferException);
}

TEST(swap,default)
{
	int a[10]={0};
	int b[10]={0};
	
	srand(time(NULL));

	for (int i=0; i<10; i++)
	{
		a[i]=rand()%65536;
		b[i]=rand()%65536;
	}

	CircularBuffer<int> c(10);
	CircularBuffer<int> d(10);

	for (int i=0; i<10; i++)
	{
		c.push_back(a[i]);
		d.push_back(b[i]);
	}

	CircularBuffer<int> e(5,117);

	EXPECT_THROW(e.swap(c),CircularBufferException);
	EXPECT_THROW(d.swap(e),CircularBufferException);

	c.swap(d);

	for (int i=0; i<10; i++)
	{
		EXPECT_EQ(c.at(i),b[i]);
		EXPECT_EQ(d.at(i),a[i]);
	}

	d.swap(c);

	for (int i=0; i<10; i++)
	{
		EXPECT_EQ(c.at(i),a[i]);
		EXPECT_EQ(d.at(i),b[i]);
	}
}

TEST(push_back,default)
{
	int a[10]={0};

	srand(clock());

	for (int i=0; i<10; i++)
	{
		a[i]=rand();
	}

	CircularBuffer<int> b(10);

	for (int i=0; i<10; i++)
	{
		b.push_back(a[i]);
	}

	for (int i=0; i<10; i++)
	{
		EXPECT_EQ(b.at(i),a[i]);
	}
}

TEST(push_front,default)
{
	int a[10]={0};

	srand(clock());

	for (int i=0; i<10; i++)
	{
		a[i]=rand();
	}

	CircularBuffer<int> b(10);

	for (int i=9; i>=0; i--)
	{
		b.push_front(a[i]);
	}

	for (int i=0; i<10; i++)
	{
		EXPECT_EQ(b.at(i),a[i]);
	}
}

TEST(pop_back,default)
{
	int a[10]={0};

	srand(clock());

	for (int i=0; i<10; i++)
	{
		a[i]=rand();
	}

	CircularBuffer<int> b(10);

	EXPECT_THROW(b.pop_back(),CircularBufferException);

	for (int i=0; i<10; i++)
	{
		b.push_front(a[i]);
	}

	for (int i=0; i<10; i++)
	{
		EXPECT_EQ(b.pop_back(),a[i]);

		EXPECT_EQ(b.size(), 9-i);
	}

	EXPECT_THROW(b.pop_back(),CircularBufferException);
}

TEST(pop_front,default)
{
	int a[10]={0};

	srand(clock());

	for (int i=0; i<10; i++)
	{
		a[i]=rand();
	}

	CircularBuffer<int> b(10);

	EXPECT_THROW(b.pop_front(), CircularBufferException);

	for (int i=0; i<10; i++)
	{
		b.push_back(a[i]);
	}

	for (int i=0; i<10; i++)
	{
		EXPECT_EQ(b.pop_front(), a[i]);

		EXPECT_EQ(b.size(), 9-i);
	}

	EXPECT_THROW(b.pop_front(), CircularBufferException);
}

TEST(insert,default)
{
	int a[10]={0};

	srand(clock());

	for (int i=0; i<10; i++)
	{
		a[i]=rand();
	}

	CircularBuffer<int> b(10,0);

	for (int i=0; i<10; i++)
	{
		b.insert(i,a[i]);
	}

	EXPECT_THROW(b.insert(-5, 5), CircularBufferException);
	EXPECT_THROW(b.insert(12, 5), CircularBufferException);

	for (int i=0; i<10; i++)
	{
		EXPECT_EQ(b.at(i), a[i]);
	}
}

TEST(erase,default)
{
	int a[10]={0};

	srand(clock());
	
	for (int i=0; i<10; i++)
	{
		a[i]=i;
	}

	CircularBuffer<int> b(10);

	for (int i=0; i<10; i++)
	{
		b.push_back(a[i]);
	}

	EXPECT_EQ(b.capacity(), 10);

	b.erase(3,7);

	EXPECT_EQ(b.capacity(), 10);
	
	EXPECT_EQ(b.size(), 6);

	for (int i=0; i<3; i++)
	{
		EXPECT_EQ(b.at(i), a[i]);
	}

	for (int i=3; i<6; i++)
	{
		EXPECT_EQ(b.at(i), a[i+4]);
	}

	EXPECT_THROW(b.at(6), CircularBufferException);
}

TEST(clear,default)
{
	CircularBuffer<int> a(10,0);

	EXPECT_EQ(a.size(),10);
	EXPECT_EQ(a.capacity(),10);
	EXPECT_EQ(a.reserve(),0);
	EXPECT_EQ(a.empty(),false);
	
	a.clear();

	EXPECT_EQ(a.size(),0);
	EXPECT_EQ(a.capacity(),10);
	EXPECT_EQ(a.reserve(),10);
	EXPECT_EQ(a.empty(),true);
}

int main(int argc, char ** argv)
{
	::testing::InitGoogleTest(&argc,argv);

	return RUN_ALL_TESTS();
}
