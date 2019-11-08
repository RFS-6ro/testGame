#include <iostream>
#include <vector>

struct vec3 {
	float x;
	float y;
	float z;
};

void find_all_faces_with_vert(std::vector<int> triag_verts, const int* faces, int nfaces, int vertIndec);
void calc_triag_vert_indeces(int * triag_indeces, int vert_indec);
vec3 calc_triag_side_vec(const vec3 * verts, int start_indec, int end_indec);
vec3 calc_face_norm(vec3 A, vec3 B);


///<summary>
///calculate average normals to mesh verts
///</summary>
void calc_mesh_normals(vec3* normals, const vec3* verts, const int* faces, int nverts, int nfaces)
{
	//vector with vert indeces from faces array
	std::vector<int> triag_verts;
	//vector with faces normals
	std::vector<vec3> faces_normals;
	//array with triangle verts indeces from faces array
	int* triag_indeces = new int[3];

	vec3 first_triang_side, second_triang_side, norm;

	int number_of_normals = 0;

	for (int vert_indec = 0; vert_indec < nverts; vert_indec++)
	{
		//set normal to zero
		normals[vert_indec].x = 0;
		normals[vert_indec].y = 0;
		normals[vert_indec].z = 0;

		//push all vertex indeces 
		find_all_faces_with_vert(triag_verts, faces, nfaces, vert_indec);

		for (int triag_vert : triag_verts)
		{
			//calculate all vert indeces of current face
			calc_triag_vert_indeces(triag_indeces, triag_vert);

			//calculate 2 triang sides with begin in current vertex
			first_triang_side = calc_triag_side_vec(verts, triag_indeces[0], triag_indeces[1]);
			second_triang_side = calc_triag_side_vec(verts, triag_indeces[0], triag_indeces[2]);

			//calculate face normal
			norm = calc_face_norm(first_triang_side, second_triang_side);

			//push triang normal
			faces_normals.push_back(norm);
		}

		//for all norm in faces normals
		for (vec3 norm : faces_normals)
		{
			//summ normals
			normals[vert_indec].x += norm.x;
			normals[vert_indec].y += norm.y;
			normals[vert_indec].z += norm.z;
		}

		//calculate average normal
		number_of_normals = faces_normals.size();
		normals[vert_indec].x /= number_of_normals;
		normals[vert_indec].y /= number_of_normals;
		normals[vert_indec].z /= number_of_normals;

		//clear vectors
		triag_verts.clear();
		faces_normals.clear();
	}

	//free allocated memory
	delete[] triag_indeces;
}

///<summary>
///find all faces that include current vert
///</summary>
void find_all_faces_with_vert(std::vector<int> triag_verts, const int* faces, int nfaces, int vertIndec)
{
	//enumeration indec triplets
	for (int face_vert_indec = 0; face_vert_indec < nfaces; face_vert_indec++)
	{
		//if triplet contain current vertex indec
		if (faces[face_vert_indec] == vertIndec)
		{
			//push it into indeces vector
			triag_verts.push_back(face_vert_indec);
		}
	}
}

///<summary>
///calculate triangle verts indeces 
///</summary>
///<param name='triag_indeces'>[0] - current vert indec [1,2] - other verts</param>
void calc_triag_vert_indeces(int * triag_indeces, int vert_indec)
{
	triag_indeces[0] = vert_indec;
	if (vert_indec % 3 == 0)
	{
		triag_indeces[1] = vert_indec + 1;
		triag_indeces[2] = vert_indec + 2;
	}
	else if (vert_indec % 3 == 1)
	{
		triag_indeces[1] = vert_indec - 1;
		triag_indeces[2] = vert_indec + 1;
	}
	else
	{
		triag_indeces[1] = vert_indec - 1;
		triag_indeces[2] = vert_indec - 2;
	}
}

///<summary>
///calculate coord of triang side
///</summary>
///<returns>vec3 with side coords</returns>
vec3 calc_triag_side_vec(const vec3 * verts, int start_indec, int end_indec)
{
	vec3 side;
	side.x = verts[end_indec].x - verts[start_indec].x;
	side.y = verts[end_indec].y - verts[start_indec].y;
	side.z = verts[end_indec].z - verts[start_indec].z;
	return side;
}

///<summary>
///calculate face normal
///</summary>
///<returns>vec3 with face norm coords</returns>
vec3 calc_face_norm(vec3 A, vec3 B)
{
	vec3 face_norm;
	face_norm.x = A.y * B.z - A.z * B.y;
	face_norm.y = A.z * B.x - A.x * B.z;
	face_norm.z = A.x * B.y - A.y * B.x;
	return face_norm;
}

int main()
{
	return 0;
}