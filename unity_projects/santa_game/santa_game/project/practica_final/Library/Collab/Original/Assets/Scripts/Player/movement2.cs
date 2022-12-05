using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class movement2 : MonoBehaviour
{
    //[RequireComponent(typeof(Rigidbody))]
    // [RequireComponent(typeof(CapsuleCollider))]
    //[RequireComponent(typeof(Animator))]



    [SerializeField] float JumpPower = 12f;
    [SerializeField] float m_GroundCheckDistance = 0.1f;
    Rigidbody m_Rigidbody;
    Animator m_Animator;
    bool ground;
    float m_OrigGroundCheckDistance;
    const float k_Half = 0.5f;
    float m_CapsuleHeight;
    Vector3 m_CapsuleCenter;
    CapsuleCollider m_Capsule;
    bool Crouching;
    bool m_Jump = false;

    float x;
    float y;
    Vector3 m_GroundNormal;

    void Start()
    {
        m_Animator = GetComponent<Animator>();
        m_Rigidbody = GetComponent<Rigidbody>();
        m_Capsule = GetComponent<CapsuleCollider>();
        m_CapsuleHeight = m_Capsule.height;
        m_CapsuleCenter = m_Capsule.center;

        m_Rigidbody.constraints = RigidbodyConstraints.FreezeRotationX | RigidbodyConstraints.FreezeRotationY | RigidbodyConstraints.FreezeRotationZ;
        m_OrigGroundCheckDistance = m_GroundCheckDistance;
    }
    private void FixedUpdate()
    {
        CheckGroundStatus();
        m_Jump = Input.GetButtonDown("Jump");
        x = Input.GetAxis("Horizontal");
        y = Input.GetAxis("Vertical");
        bool crouch = Input.GetKey(KeyCode.C);
        if (!Input.GetKey(KeyCode.LeftShift)) y *= 0.5f;

        transform.Rotate(0, x * Time.deltaTime * 100, 0);
        transform.Translate(0, 0, y * Time.deltaTime * 5);
        
        m_Animator.SetFloat("Forward", y, 0.1f, Time.deltaTime);
        m_Animator.SetFloat("Turn", x, 0.1f, Time.deltaTime);
        m_Animator.SetBool("Crouch", Crouching);
        m_Animator.SetBool("OnGround", ground);

        
        PreventStandingInLowHeadroom();
        ScaleCapsuleForCrouching(crouch);
        Jump(crouch, m_Jump);
        if (!ground){ m_Animator.SetFloat("Jump", 1);}
        else { m_Animator.SetFloat("JumpLeg", 1);}
        


    }

    
    void PreventStandingInLowHeadroom()
    {
        
        if (!Crouching)
        {
            Ray crouchRay = new Ray(m_Rigidbody.position + Vector3.up * m_Capsule.radius * k_Half, Vector3.up);
            float crouchRayLength = m_CapsuleHeight - m_Capsule.radius * k_Half;
            if (Physics.SphereCast(crouchRay, m_Capsule.radius * k_Half, crouchRayLength, Physics.AllLayers, QueryTriggerInteraction.Ignore))
            {
                Crouching = true;
            }
        }
    }

    void Jump(bool crouch, bool jump)
    {
        if (jump && !crouch && ground)
        {
            // jump!
            m_Rigidbody.velocity = new Vector3(m_Rigidbody.velocity.x, JumpPower, m_Rigidbody.velocity.z);
            ground = false;
            m_Animator.applyRootMotion = false;
            m_GroundCheckDistance = 0.1f;
        }
        m_GroundCheckDistance = m_OrigGroundCheckDistance;
    }

    void ScaleCapsuleForCrouching(bool crouch)
    {
        if (ground && crouch)
        {
            if (Crouching) return;
            m_Capsule.height = m_Capsule.height / 2f;
            m_Capsule.center = m_Capsule.center / 2f;
            Crouching = true;
        }
        else
        {
            Ray crouchRay = new Ray(m_Rigidbody.position + Vector3.up * m_Capsule.radius * k_Half, Vector3.up);
            float crouchRayLength = m_CapsuleHeight - m_Capsule.radius * k_Half;
            if (Physics.SphereCast(crouchRay, m_Capsule.radius * k_Half, crouchRayLength, Physics.AllLayers, QueryTriggerInteraction.Ignore))
            {
                Crouching = true;
                return;
            }
            m_Capsule.height = m_CapsuleHeight;
            m_Capsule.center = m_CapsuleCenter;
            Crouching = false;
        }
    }


    void CheckGroundStatus()
    {
        m_GroundNormal = transform.position;
        RaycastHit hitInfo;

        bool collided = Physics.Raycast(transform.position + (Vector3.up * 0.1f), Vector3.down, out hitInfo, m_GroundCheckDistance);

        if (collided && !hitInfo.collider.gameObject.CompareTag("Enviroment") && !hitInfo.collider.gameObject.CompareTag("Left Curve") && 
            !hitInfo.collider.gameObject.CompareTag("Right Curve"))
        {
            m_GroundNormal = hitInfo.normal;
            ground = true;
            m_Animator.applyRootMotion = true;
        }
        else
        {
            ground = false;
            m_GroundNormal = Vector3.up;
            m_Animator.applyRootMotion = false;

        }
    }

    
}
