#include <cyclone/particle.h>
#include <cyclone/precision.h>
#include <vector>
namespace cyclone
{
    /*
    A force generator can be asked to add a force to one or more
    particles.
    */
    class ParticleForceGenerator
    {
    public:
        /*
        Overload this in implementations of the interface to calculate
        and update the force applied to the given particle.
        */
        virtual void updateForce(Particle *particle, real duration) = 0;
    };

    /*
    Holds all the force generators and the particles they apply to.
    */
    class ParticleForceRegistry
    {
    protected:
        /*
        Keeps track of one force generator and the particle it
        applies to.
        */
        struct ParticleForceRegistration
        {
            Particle *particle;
            ParticleForceGenerator *fg;
        };

        /*
        Holds the list of registrations.
        */
        typedef std::vector<ParticleForceRegistration> Registry;
        Registry registrations;

    public:
        /*
        Registers the given force generator to apply to the
        given particle.
        */
        void add(Particle *particle, ParticleForceGenerator *fg);

        /*
        Removes the given registered pair from the registry.
        If the pair is not registered, this method will have
        no effect.
        */
        void remove(Particle *particle, ParticleForceGenerator *fg);

        /*
        Clears all registrations from the registry. This will
        not delete the particles or the force generators
        themselves, just the records of their connection.
        */
        void clear();

        /*
        Calls all the force generators to update the forces of
        their corresponding particles.
        */
        void updateForces(real duration);
    };

    /*
    A force generator that applies a gravitational force. One instance
    can be used for multiple particles.
    */
    class ParticleGravity : public ParticleForceGenerator
    {

        /* Holds the acceleration due to gravity. */
        Vector3 gravity;

    public:
        /* Creates the generator with the given acceleration. */
        ParticleGravity(const Vector3 &gravity);

        /* Applies the gravitational force to the given particle. */
        virtual void updateForce(Particle *particle, real duration);
    };

    /*
    A force generator that applies a drag force. One instance
    can be used for multiple particles.
    */
    class ParticleDrag : public ParticleForceGenerator
    {

        /* Holds the velocity drag coefficient. */
        real k1;

        /* Holds the velocity squared drag coefficient. */
        real k2;

    public:
        /* Creates the generator with the given coefficients. */
        ParticleDrag(real k1, real k2);

        /* Applies the drag force to the given particle. */
        virtual void updateForce(Particle *particle, real duration);
    };

    /*
    A force generator that applies a spring force.
    */
    class ParticleSpring : public ParticleForceGenerator
    {
        /* The particle at the other end of the spring. */
        Particle *other;

        /* Holds the spring constant. */
        real springConstant;

        /* Holds the rest length of the spring. */
        real restLength;

    public:
        /* Creates a new spring with the given parameters. */
        ParticleSpring(Particle *other,
                       real springConstant, real restLength);

        /* Applies the spring force to the given particle. */
        virtual void updateForce(Particle *particle, real duration);
    };

    /*
    A force generator that applies a spring force, where
    one end is attached to a fixed point in space.
    */
    class ParticleAnchoredSpring : public ParticleForceGenerator
    {
        /* The location of the anchored end of the spring. */
        Vector3 *anchor;

        /* Holds the spring constant. */
        real springConstant;

        /* Holds the rest length of the spring. */
        real restLength;

    public:
        /* Creates a new spring with the given parameters. */
        ParticleAnchoredSpring(Vector3 *anchor,
                               real springConstant, real restLength);

        /* Applies the spring force to the given particle. */
        virtual void updateForce(Particle *particle, real duration);
    };
}