using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Camera_3p : MonoBehaviour
{
    public Vector3 offset;
    private Transform target;
    [Range(0, 1)] public float lerpValue;
    public GameObject player;
    public bool cameraFollow = false;

    // Start is called before the first frame update
    void Start()
    {
        target = player.transform;
    }

    // Update is called once per frame
    void LateUpdate()
    {
        //transform.position = Vector3.Lerp(transform.position, target.position + offset, lerpValue);
        if (cameraFollow) transform.LookAt(target);
    }
}
