using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.EventSystems;

public class ControlAndroid : MonoBehaviour
{
    public bool jump;
    public bool leftMove;
    public bool rightMove;

    
    // Start is called before the first frame update
    void Start()
    {
        jump = false;
        leftMove = false;
        rightMove = false;
    }

    // Update is called once per frame
    void Update()
    {

    }

    public void Jump()
    {
      jump = true;
    }

    public void LeftMove()
    {
      leftMove = true;
    }

    public void RightMove()
    {
      rightMove = true;
    }

    public void ExitLevel()
    {
      SceneManager.LoadScene("Menu");
    }

    void OnCancel( BaseEventData data)
    {

    }
}
