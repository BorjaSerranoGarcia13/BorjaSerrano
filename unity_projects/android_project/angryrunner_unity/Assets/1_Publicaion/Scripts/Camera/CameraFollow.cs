using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraFollow : MonoBehaviour
{
    Camera_3p script;
    // Start is called before the first frame update
    void Start()
    {
        script = GameObject.FindGameObjectWithTag("MainCamera").GetComponent<Camera_3p>();
    }

    // Update is called once per frame
    void Update()
    {

    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.CompareTag("Player"))
        {
            if (!script.cameraFollow) script.cameraFollow = true;
            else script.cameraFollow = false;
        }
    }

}
