using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;
using UnityEngine.InputSystem.PlayerInput;

public class RetryMenu : MonoBehaviour
{
    public Image a1;
    public Image a2;

    int map;

    float movement;

    timeCounter script;

    void Start()
    {
        map = 0;
        script = GameObject.Find("ScoreManager").GetComponent<timeCounter>();
    }

    // Update is called once per frame
    void Update()
    {
      if (map == 0)
      {
        a1.color = new Vector4(0.8f, 0.9f, 1f, 1f);
        a2.color = new Vector4(0.52f, 0.52f, 0.52f, 1f);
      }
      else if (map == 1)
      {
        a1.color = new Vector4(0.52f, 0.52f, 0.52f, 1f);
        a2.color = new Vector4(1f, 0.88f, 0.88f, 1f);
      }

    }

    void OnMoveRetry(InputValue value)
    {
      if (script.currentTime <= 0)
      {
        movement = value.Get<float>();
        if (movement == 1) map++;
        if (movement == -1) map--;

        if (map > 1) map = 0;
        if (map < 0) map = 1;
      }
    }

    void OnPress(InputValue value)
    {
      if (script.currentTime <= 0)
      {
        if (map == 0)
        {
          Scene scene = SceneManager.GetActiveScene();
          SceneManager.LoadScene(scene.name);
        }
        else if (map == 1)
        {
          SceneManager.LoadScene(0);
        }
      }
    }
}
