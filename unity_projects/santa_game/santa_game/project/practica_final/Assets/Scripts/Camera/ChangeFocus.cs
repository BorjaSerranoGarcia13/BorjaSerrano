using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ChangeFocus : MonoBehaviour
{
    Camera main_camera;
    railMover mover;
    public Transform newLookAt;
    // Start is called before the first frame update
    void Start()
    {
        main_camera = Camera.main;
        mover = main_camera.GetComponent<railMover>();
    }

    // Update is called once per frame
    void Update()
    {
        
    }
    public void ChangeCameraFocus() {
        if(newLookAt!=null) mover.lookAt = newLookAt;
    }
}
