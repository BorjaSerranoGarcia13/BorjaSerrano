using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PuzzleComplete : MonoBehaviour
{
    public SwitchColor[] puzzle;
    public bool activated = false;
    public GameObject doorMove;

    void Start()
    {
        
    }

    void Update()
    {
        int total_pressed = 0;
        for (int i = 0; i < puzzle.Length; i++)
        {
            if (puzzle[i].pressed )
            {
              total_pressed += 1;
            }
        }      
        if (puzzle.Length == total_pressed)
        {
            activated = true;       
        }
        
        if (activated == true)
        {
            doorMove.transform.position += new Vector3(0.0f, 1.0f * Time.deltaTime, 0.0f);
        }
    }
}
