using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StageGenerator : MonoBehaviour {

    public List<GameObject> normalGroundPrefabs;
    public List<GameObject> specialGroundPrefabs;
    public List<GameObject> rightCurveGroundPrefabs;
    public List<GameObject> leftCurveGroundPrefabs;
    public GameObject spawnPointPrefab;

    public Vector3 position;

    public int piezes;
    public int distanceBetweenSpawns;

    public int specialGroundProb;
    public int specialGroundProbSteep;

    public int curveGroundProb;
    public int curveGroundProbSteep;

    private int specialProb;
    private int curveProb;

    private float rotation;

    private int spawnedPiezes;

    private void Start() {
        position = Vector3.zero;
        rotation = 0;

        specialProb = specialGroundProb;
        curveProb = curveGroundProb;

        GenerateAll();
    }

    private void Generate() {
        int type = Random.Range(0, 100);

        List<GameObject> groundType;
        GameObject groundObject;

        if (spawnedPiezes % distanceBetweenSpawns == 0) {
            GameObject.Instantiate(spawnPointPrefab, position + Vector3.up, Quaternion.Euler(0.0f, rotation, 0.0f));
        }

        if (type < specialProb) {
            groundType = specialGroundPrefabs;
            specialProb = specialGroundProb;
        } else {
            type = Random.Range(0, 100);

            if (type < curveGroundProb) {

                type = Random.Range(0, 2);

                if (rotation < 90 && type == 0) {
                    groundType = rightCurveGroundPrefabs;
                    curveProb = curveGroundProb;
                } else if (rotation > -90 && type == 1) {
                    groundType = leftCurveGroundPrefabs;
                    curveProb = curveGroundProb;
                } else {
                    groundType = normalGroundPrefabs;
                }
            } else {
                groundType = normalGroundPrefabs;
                curveProb =  Mathf.Clamp(curveProb + curveGroundProbSteep, 0, 100);
            }

            specialProb =  Mathf.Clamp(specialProb + specialGroundProbSteep, 0, 100);
        }

        type = Random.Range(0, groundType.Count);

        groundObject = GameObject.Instantiate(groundType[type], position, Quaternion.identity);
        spawnedPiezes++;

        if (groundType == leftCurveGroundPrefabs || groundType == rightCurveGroundPrefabs) {
            position.z += groundObject.GetComponent<BoxCollider>().bounds.extents.z - 1;
            groundObject.transform.Rotate(Vector3.up * rotation);
            if (groundType == rightCurveGroundPrefabs) {
                rotation += 90;
            } else {
                rotation -= 90;
            }

            if (rotation != 0.0f) {
                if (rotation == 90) {
                    position.x += groundObject.GetComponent<BoxCollider>().bounds.extents.x + 1;

                } else{
                    position.x -= groundObject.GetComponent<BoxCollider>().bounds.extents.x + 1;
                }
            } else {
                position.z += 2;
                if (groundType == rightCurveGroundPrefabs) {
                    position.x -= groundObject.GetComponent<BoxCollider>().bounds.extents.x - 1;
                } else {
                    position.x += groundObject.GetComponent<BoxCollider>().bounds.extents.x - 1;
                }
            }

        } else {
            if (rotation > 0 && rotation <= 90) {
                position.x += groundObject.GetComponent<BoxCollider>().bounds.size.z;
            } else if (rotation < 0 && rotation >= -90) {
                position.x -= groundObject.GetComponent<BoxCollider>().bounds.size.z;
            } else {
                position.z += groundObject.GetComponent<BoxCollider>().bounds.size.z;
            }
            groundObject.transform.Rotate(Vector3.up * rotation);
        }


    }

    private void GenerateAll() {
        Generate(piezes);
    }

    public void Generate(int i) {
        for (int j = 0; j < i; ++j) {
            Generate();
        }
    }
}
