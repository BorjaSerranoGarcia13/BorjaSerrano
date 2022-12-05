using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FishMov : MonoBehaviour
{
    [SerializeField]
    bool activate_mov = true;

    private bool Jumpped;
    public float JumpSpeed;

    private Animator animator;

    // Start is called before the first frame update
    void Start()
    {
        Jumpped = true;
        animator = GetComponent<Animator>();
        JumpSpeed = 300.0f;
    }

    // Update is called once per frame
    void Update()
    {
        if (activate_mov)
        {
  
            if (Jumpped)
            {
                Vector3 tmp = new Vector3(0.0f, 1.0f, 0.0f);
                GetComponent<Rigidbody>().velocity = JumpSpeed * transform.up * Time.deltaTime;
                
                Debug.Log( JumpSpeed * transform.up);
                animator.SetBool("angry", true);
                Jumpped = false;
            }
            else
            {
                animator.SetBool("angry", false);
            }
        }
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.CompareTag("Jump"))
        {
            Jumpped = true;
        }
    }


}
