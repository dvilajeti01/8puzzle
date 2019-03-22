
#include <iostream>
#include <string>
using namespace std;

void rand_array(int real_arr[])
{
	int count = 0;
	int num;
	bool exists = 0;

	for (int i = 2; i >= 0; i--)
	{
		count = 0;
		cout << "--------" << i << "--------" << endl;
		while (count == 0)
		{
			num = rand() % 3;


			for (int j = i + 1; j < 3; j++)
			{
				cout << "num:" << num << endl << "curr:" << real_arr[j] << endl;
				if (real_arr[j] == num)
				{
					cout << "HIT2" << endl;
					exists = true;
					break;
				}
				else
					exists = false;
			}

			if (exists == false)
			{
				cout << "HIT" << endl;
				real_arr[i] = num;
				count = 1;
			}
		}
	}

}

int main(int argc, const char * argv[]) {
	
	int num;
	int real_arr[3];

	rand_array(real_arr);

	for (int i = 0; i < 3; i++)
	{
		cout<<real_arr[i]<<endl;
		
	}

	rand_array(real_arr);

	for (int i = 0; i < 3; i++)
	{
		cout << real_arr[i] << endl;

	}

	cin >> num;
	return 0;
}
