using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class dead_script : MonoBehaviour {
    Canvas canvas;
    // Use this for initialization
    void Start () {
        canvas = GetComponent<Canvas>();
        canvas.enabled = false;
    }
	
	// Update is called once per frame
	void Update () {

        if (GameObject.FindGameObjectsWithTag("Player").Length == 0)
        {
            canvas.enabled = true;
            
        }
    }
}
