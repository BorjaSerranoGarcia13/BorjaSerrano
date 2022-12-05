using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Camera_3p : MonoBehaviour
{
    public Vector3 offset;
    private Transform target;
    [Range(0, 1)] public float lerpValue;
    public bool cameraFollow = false;

    GameObject tmp;

    float tmpY;

    // Start is called before the first frame update
    void Start()
    {
        tmp = GameObject.FindWithTag("Player");
        target = tmp.transform;
        tmpY = target.position.y;
    }

    // Update is called once per frame
    void LateUpdate()
    {
        //if (tmp.transform.position.x <= -12) cameraFollow = false;
        //else cameraFollow = true;
        if (cameraFollow)
        {
            Vector3 hh = target.position;
            hh.y = tmpY;
            transform.position = Vector3.Lerp(transform.position, hh + offset, lerpValue);
            //if (cameraFollow) transform.LookAt(target);

        }
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.CompareTag("LimitTerrain"))
        {
            cameraFollow = false;
            Debug.Log("ss");
        }
    }
}
