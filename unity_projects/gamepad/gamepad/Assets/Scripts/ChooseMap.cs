using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem.PlayerInput;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class ChooseMap : MonoBehaviour
{
    float movement;
    float direction;
    int pressed;

    public Image a1;
    public Image a2;
    public Image a3;

    int map;

    void Start()
    {
      map = 0;
    }

    // Update is called once per frame
    void Update()
    {
      if (map == 0)
      {
        a1.color = new Vector4(1.0f, 0.5f, 0.5f, 1f);
        a2.color = new Vector4(0.72f, 0.72f, 0.72f, 1f);
        a3.color = new Vector4(0.72f, 0.72f, 0.72f, 1f);
      }
      else if (map == 1)
      {
        a1.color = new Vector4(0.72f, 0.72f, 0.72f, 1f);
        a2.color = new Vector4(0.5f, 0.5f, 0.9f, 1f);
        a3.color = new Vector4(0.72f, 0.72f, 0.72f, 1f);
      }
      else if (map == 2)
      {
        a1.color = new Vector4(0.72f, 0.72f, 0.72f, 1f);
        a2.color = new Vector4(0.72f, 0.72f, 0.72f, 1f);
        a3.color = new Vector4(0.63f, 1f, 0.43f, 1f);
      }
    }

    void OnMoveMenu(InputValue value)
    {
      movement = value.Get<float>();

      if (movement == 1) map++;
      if (movement == -1) map--;

      if (map > 2) map = 0;
      if (map < 0) map = 2;
    }

    void OnPress(InputValue value)
    {
      if (map == 0)
      {
        SceneManager.LoadScene(1);
      }
      else if (map == 1)
      {
        SceneManager.LoadScene(2);
      }
      else if (map == 2)
      {
        SceneManager.LoadScene(3);
      }
    }
}
