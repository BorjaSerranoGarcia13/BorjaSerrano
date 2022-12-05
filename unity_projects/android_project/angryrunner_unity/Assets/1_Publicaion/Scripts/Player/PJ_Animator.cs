using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PJ_Animator : MonoBehaviour
{
    private Animator animator;
    // Start is called before the first frame update
    void Start()
    {
        animator = GetComponent<Animator>();
    }

    // Update is called once per frame
    void Update()
    {

      if (Input.GetKey("left") || Input.GetKey("right"))
      {
        animator.SetBool("running", true);
      }
      else
      {
        animator.SetBool("running", false);
      }

      if (Input.GetKeyDown("space"))
      {
        animator.SetBool("jumping", true);
      }
      else
      {
        animator.SetBool("jumping", false);
      }
    }
}
