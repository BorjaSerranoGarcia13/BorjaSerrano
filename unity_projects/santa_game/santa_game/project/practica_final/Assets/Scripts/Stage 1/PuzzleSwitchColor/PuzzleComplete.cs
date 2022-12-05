using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PuzzleComplete : MonoBehaviour
{
    public SwitchColor[] puzzle;
    public bool activated = false;
    public GameObject doorMove;
    int count = 0;
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

        if (activated == true && count < 2000)
        {
            doorMove.transform.position += new Vector3(0.0f, 1.0f * Time.deltaTime, 0.0f);
            count += 1;
        }
        if (count >= 2000)
        {
          doorMove.transform.position = new Vector3(0,0,0);
        }
    }
}
