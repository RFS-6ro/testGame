#include <iostream>
#include <cstdio>
#include <string>

struct ListNode
{
	ListNode *	prev;
	ListNode *	next;
	ListNode *	rand;

	std::string data;
};

class List
{
public:
	List()
	{

	}
	~List()
	{

	}

	///<summary>
	///save linked list to binary file
	///</summary>
	void Serialize(FILE * file)
	{
		fwrite(&count, sizeof(int), sizeof(count), file);
		if (count == 0) return;

		std::string write_data;

		ListNode * write_node;
		write_data = head->data;
		fwrite(&write_data, sizeof(write_data), 1, file);

		//get indec of rand listnode from head
		int rand_list_node_indec = get_indec_of_random_pointer(head->rand);
		fwrite(&rand_list_node_indec, sizeof(int), 1, file);
		write_node = head->next;

		for (int i = 0; i < count - 1; i++)
		{
			write_data = write_node->data;
			fwrite(&write_data, sizeof(write_data), 1, file);
			//get indec of rand listnode from written node
			rand_list_node_indec = get_indec_of_random_pointer(write_node->rand);
			fwrite(&rand_list_node_indec, sizeof(int), 1, file);
			write_node = write_node->next;
		}
	}

	///<summary>
	///restore linked list from binary file
	///</summary>
	void Deserialize(FILE * file)
	{
		fread(&count, sizeof(int), sizeof(count), file);
		if (count == 0) return;

		head = new ListNode;
		tail = new ListNode;

		std::string read_node_data;
		int read_indec;
		ListNode * temp_node = head;
		//list random node indeces array
		int * rand_node_indeces = new int[count];

		fread(&read_node_data, sizeof(std::string), 1, file);
		head->data = read_node_data;

		fread(&read_indec, sizeof(int), 1, file);
		rand_node_indeces[0] = read_indec;

		for (int i = 1; i < count; i++)
		{
			//allocate memory to node
			ListNode * node = new ListNode;

			//head check
			if (i == 1)
			{
				head->prev = NULL;
				head->next = node;
			}

			fread(&read_node_data, sizeof(std::string), 1, file);			

			fread(&read_indec, sizeof(int), 1, file);
			rand_node_indeces[i] = read_indec;

			//tail check
			if (i == count - 1)
			{
				tail->data = read_node_data;
				tail->prev = temp_node;
				tail->next = NULL;
			}
			else
			{
				node->data = read_node_data;

				node->prev = temp_node;
				temp_node = node;
			}
		}

		//complete linked list structure
		temp_node = tail;
		ListNode * node = tail->prev;

		for (int i = count - 1; i > 0; i--)
		{
			node->next = temp_node;
			node->rand = get_random_pointer_by_indec(rand_node_indeces[i]);

			temp_node = node;
			node = node->prev;
		}

		//free allocated memory
		delete[] rand_node_indeces;
	}

private:
	///<summary>
	///get node indec in list via pointer
	///</summary>
	int get_indec_of_random_pointer(ListNode * rnd)
	{
		int indec = 0;

		while (rnd->prev != NULL)
		{
			indec++;
			rnd = rnd->prev;
		}

		return indec;
	}

	///<summary>
	///get pointer on list node by indec
	///</summary>
	ListNode * get_random_pointer_by_indec(int node_indec)
	{
		ListNode * node;
		node = head;

		for (int i = 0; i < node_indec; i++)
		{
			node = node->next;
		}

		return node;
	}

	ListNode *	head;
	ListNode *	tail;
	int count;
};