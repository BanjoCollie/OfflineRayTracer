// RayTracer.cpp : Defines the entry point for the application.
//

#include <string>
#include <sstream>
#include "RayTracer.h"

using namespace std;


void AddTexture(string fileName, vector<Texture*>& vec);

int main(int argc, char* argv[])
{
	// Setup rand for all future uses
	srand(static_cast <unsigned> (time(0)));


	// Query the user for the input file location
	string inputFileName = "";
	//argc = 0;
	if (argc == 0)
	{
		cout << "Enter input file name:" << endl;
	}
	else
	{
		cout << argc << " arguments entered" << endl;
		inputFileName = argv[1];
		cout << "Running RayTracer with file " + inputFileName + "..." << endl;
		if (inputFileName.size() < 5 || inputFileName.substr(inputFileName.size() - 4) != ".txt")
		{
			inputFileName = "";
			cout << "File name entered is invalid, please enter a new filename" << endl;
		}
	}
	while (inputFileName == "")
	{
		cin >> inputFileName;
		if (inputFileName.size() < 5 || inputFileName.substr(inputFileName.size() - 4) != ".txt")
		{
			inputFileName = "";
			cout << "File type must be .txt" << endl << "Please enter a new file name" << endl;
		}
	}

	// Open input file
	ifstream inputFile;
	inputFile.open(inputFileName);
	if (!inputFile.is_open())
	{
		cout << "ERROR - Failed to open input file" << endl;
		return 0;
	}

	Scene mainScene;

	Vector3 eye;
	Vector3 viewdir;
	Vector3 updir;
	float vfov = 0;
	Vector2 imsize;
	Color bkcolor;

	vector<Material*> materials;
	int materialIndex = -1;

	vector<Texture*> textures;
	int textureIndex = -1;

	string lastDataType = "";
	// Read data from file
	string lastLine;
	while (getline(inputFile, lastLine))
	{
		stringstream sStream(lastLine);

		string dataType;
		sStream >> dataType;
		cout << "Reading setting for " << dataType << "..." << endl;
		if (dataType == "eye")
		{
			sStream >> eye.x >> eye.y >> eye.z;
		}
		else if (dataType == "viewdir")
		{
			sStream >> viewdir.x >> viewdir.y >> viewdir.z;
		}
		else if (dataType == "updir")
		{
			sStream >> updir.x >> updir.y >> updir.z;
		}
		else if (dataType == "vfov")
		{
			sStream >> vfov;
		}
		else if (dataType == "imsize")
		{
			sStream >> imsize.x >> imsize.y;
		}
		else if (dataType == "bkgcolor")
		{
			sStream >> bkcolor.r >> bkcolor.g >> bkcolor.b;
		}
		else if (dataType == "mtlcolor")
		{
			Color diffColor, specColor;
			float kA, kD, kS, n, opacity, refraction;
			sStream >> diffColor.r >> diffColor.g >> diffColor.b
				>> specColor.r >> specColor.g >> specColor.b
				>> kA >> kD >> kS >> n >> opacity >> refraction;
			materials.push_back(new Material(diffColor, specColor, kA, kD, kS, n, opacity, refraction));
			materialIndex++;
		}
		else if (dataType == "sphere")
		{
			Vector3 pos(0, 0, 0);
			float r;
			sStream >> pos.x >> pos.y >> pos.z >> r;
			if (textureIndex != -1)
				mainScene.AddSphere(pos, r, materials[materialIndex], textures[textureIndex]);
			else
				mainScene.AddSphere(pos, r, materials[materialIndex]);
		}
		else if (dataType == "ellipsoid")
		{
			Vector3 pos(0, 0, 0);
			Vector3 r(0, 0, 0);
			sStream >> pos.x >> pos.y >> pos.z >> r.x >> r.y >> r.z;
			mainScene.AddEllipsoid(pos, r, materials[materialIndex]);
		}
		else if (dataType == "v")
		{
			Vector3 pos;
			sStream >> pos.x >> pos.y >> pos.z;
			mainScene.AddPoint(pos);
		}
		else if (dataType == "vn")
		{
			Vector3 norm;
			sStream >> norm.x >> norm.y >> norm.z;
			mainScene.AddNormal(norm);
		}
		else if (dataType == "vt")
		{
			Vector2 uv;
			sStream >> uv.x >> uv.y;
			mainScene.AddUV(uv);
		}
		else if (dataType == "f")
		{
			int p1, p2, p3, n1, n2, n3, t1, t2, t3;
			char slash;
			p1 = p2 = p3 = n1 = n2 = n3 = t1 = t2 = t3 = 0;
			int slashPos = lastLine.find_first_of('/');
			if (slashPos != string::npos)
			{
				int secondSlashPos = lastLine.find_first_of('/', slashPos+1);
				if (secondSlashPos == slashPos+1)
				{
					// Normals, no textures
					sStream >> p1 >> slash >> slash >> n1
						>> p2 >> slash >> slash >> n2
						>> p3 >> slash >> slash >> n3;
				}
				else
				{
					int spacePos = lastLine.find_first_of(' ', slashPos + 1);
					if (spacePos > secondSlashPos)
					{
						// Normals and textures
						sStream >> p1 >> slash >> t1 >> slash >> n1
							>> p2 >> slash >> t2 >> slash >> n2
							>> p3 >> slash >> t3 >> slash >> n3;
					}
					else
					{
						// Textures, no normals
						sStream >> p1 >> slash >> t1
							>> p2 >> slash >> t2
							>> p3 >> slash >> t3;
					}
				}
			}
			else
			{
				// No normals or textures
				sStream >> p1 >> p2 >> p3;
			}

			if (textureIndex != -1)
				mainScene.AddTriangle(p1-1, p2-1, p3-1, 
					t1 - 1, t2 - 1, t3 - 1, 
					n1 - 1, n2 - 1, n3 - 1, 
					materials[materialIndex], textures[textureIndex]);
			else
				mainScene.AddTriangle(p1 - 1, p2 - 1, p3 - 1,
					t1 - 1, t2 - 1, t3 - 1,
					n1 - 1, n2 - 1, n3 - 1,
					materials[materialIndex], nullptr);
		}
		else if (dataType == "light")
		{
			Vector4 pos(0,0,0,0);
			Color col(0,0,0);
			sStream >> pos.x >> pos.y >> pos.z >> pos.w
				>> col.r >> col.g >> col.b;
			mainScene.AddLight(pos, col);
		}
		else if (dataType == "attlight")
		{
			Vector4 pos(0, 0, 0, 0);
			Color col(0, 0, 0);
			float a, b, c;
			sStream >> pos.x >> pos.y >> pos.z >> pos.w
				>> col.r >> col.g >> col.b
				>> a >> b >> c;
			mainScene.AddLight(pos, col, a, b, c);
		}
		else if (dataType == "spotlight")
		{
			Vector3 pos, dir;
			float theta;
			Color myColor;

			sStream >> pos.x >> pos.y >> pos.z
				>> dir.x >> dir.y >> dir.z
				>> theta
				>> myColor.r >> myColor.g >> myColor.b;
			mainScene.AddSpotLight(Vector4(pos, 1), myColor, theta, dir);
		}
		else if (dataType == "attspotlight")
		{
			Vector3 pos(0, 0, 0);
			Vector3 dir;
			Color col(0, 0, 0);
			float theta, a, b, c;
			sStream >> pos.x >> pos.y >> pos.z
				>> dir.x >> dir.y >> dir.z
				>> theta 
				>> col.r >> col.g >> col.b
				>> a >> b >> c;
			mainScene.AddSpotLight(Vector4(pos, 1), col, theta, dir, a, b, c);
		}
		else if (dataType == "texture")
		{
			string fileName;
			sStream >> fileName;
			AddTexture(fileName, textures);
			textureIndex++;
		}
		else
		{
			cout << "ERROR - File format is invalid - invalid keyword is \"" << dataType << "\"" << endl;
			cout << "Possible that " << lastDataType << " feild has the wrong number or parameters" << endl;
			return 0;
		}
		lastDataType = dataType;
	}

	if (viewdir.IsParallel(updir))
	{
		cout << "ERROR - View direction cannot be parellel to the up direction" << endl;
		return 0;
	}

	if (imsize.x == 0 || imsize.y == 0)
	{
		cout << "ERROR - image size must be above 0 in both dimensions" << endl;
		return 0;
	}

	if (vfov == 0)
	{
		cout << "ERROR - feild of view must be greater than 0" << endl;
		return 0;
	}

	Camera mainCam(
		eye,
		viewdir,
		updir,
		vfov,
		imsize,
		bkcolor
	);

	string outputFileName = inputFileName;
	outputFileName.replace(outputFileName.end() - 4, outputFileName.end(), ".ppm");

	ofstream output;
	output.open(outputFileName, std::ios::trunc);
	if (!output.is_open())
	{
		std::cout << "Failed to create output file" << std::endl;
	}
	else
	{
		mainCam.Draw(mainScene, output);
	}

	return 0;
}


void AddTexture(string fileName, vector<Texture*>& vec)
{
	ifstream fileStream;
	fileStream.open(fileName);
	if (!fileStream.is_open())
	{
		cout << "ERROR - Failed to open texture" << endl;
		// probably want to exit the whole program here
		return;
	}

	string p;
	fileStream >> p;
	if (p != "P3")
	{
		cout << "ERROR - Texture \"" + fileName + "\" does not start with P3" << endl;
	}
	int width, height, maxVal;
	fileStream >> width >> height >> maxVal;

	int size = width * height;
	Color** colorBuff = new Color * [size];

	for (int i = 0; i < size; i++)
	{
		float r, g, b;
		fileStream >> r >> g >> b;
		if (fileStream.fail())
		{
			cout << "Texture \"" + fileName + "\" width or height entered incorrectly";
			break;
		}
		r /= maxVal;
		g /= maxVal;
		b /= maxVal;
		Color* newCol = new Color(r, g, b);
		colorBuff[i] = newCol;
	}

	Texture* newTex = new Texture(colorBuff, width, height, maxVal);

	vec.push_back(newTex);

}