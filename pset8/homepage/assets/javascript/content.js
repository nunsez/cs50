const pages = [
    { id: 'main', href: '/index.html', title: 'Main' },
    { id: 'cats', href: '/pets/cats.html', title: 'Cats' },
    { id: 'dogs', href: '/pets/dogs.html', title: 'Dogs' },
    { id: 'hamsters', href: '/pets/hamsters.html', title: 'Hamsters' },
    { id: 'turtles', href: '/pets/turtles.html', title: 'Turtles' },
]

const cats = [
    {
        breed: 'Abyssinian',
        src: '/assets/images/cats/abyssinian.jpg',
        text: 'Abyssinians are highly intelligent and intensely inquisitive. They love to investigate and will leave no nook or cranny unexplored. They’re sometimes referred to as “Aby-grabbys” because they tend to take things that grab their interest.',
    },
    {
        breed: 'Balinese-Javanese',
        src: '/assets/images/cats/javanese.jpg',
        text: 'The Balinese, also known as Javanese depending on coat color and pattern, is regal and aristocratic in appearance, but a curious kitten at heart.',
    },
    {
        breed: 'Chartreux',
        src: '/assets/images/cats/chartreux.jpg',
        text: 'Often called the smiling cat of France, the Chartreux has a sweet, smiling expression. This sturdy, powerful cat has a distinctive blue coat with a resilient wooly undercoat.',
    },
    {
        breed: 'Himalayan',
        src: '/assets/images/cats/himalayan.jpg',
        text: 'The Himalayan Cat is a sweet and mild-tempered feline. She’s affectionate but selective. Although she loves lying in your lap and being pet, she may be reserved around guests.',
    },
]

const dogs = [
    {
        breed: 'Alaskan Malamute',
        src: '/assets/images/dogs/alaskan.jpg',
        text: 'An immensely strong, heavy-duty worker of spitz type, the Alaskan Malamute is an affectionate, loyal, and playful but dignified dog recognizable by his well-furred plumed tail carried over the back, erect ears, and substantial bone.',
    },
    {
        breed: 'Bulldog',
        src: '/assets/images/dogs/bulldog.jpg',
        text: 'Bulldogs are a well-balanced athletic dog that demonstrate great strength, endurance, agility, and a friendly attitude. Historically, they were bred to be a utility dog used for working the farm.',
    },
    {
        breed: 'Dalmatian',
        src: '/assets/images/dogs/dalmatian.jpg',
        text: 'The dignified Dalmatian, dogdom\'s citizen of the world, is famed for his spotted coat and unique job description. During their long history, these "coach dogs" have accompanied the horse-drawn rigs of nobles, gypsies, and firefighters.',
    },
    {
        breed: 'Russian Toy',
        src: '/assets/images/dogs/russian-toy.jpg',
        text: 'The Russian Toy is a small, elegant, lively dog with long legs, fine bones and lean muscles. They are active and cheerful, possessing keen intelligence and a desire to please.',
    },
]

const hamsters = [
    {
        breed: 'Syrian',
        src: '/assets/images/hamsters/syrian.jpg',
        text: 'Your Syrian Hamster might not have a golden coat, or any of the coat colors we’ve mentioned so far. Don’t worry. Since humans domesticated Syrian hamsters, we’ve introduced a whole host of coat colors.',
    },
    {
        breed: 'Dwarf Campbell Russian',
        src: '/assets/images/hamsters/campbell.jpg',
        text: 'There are two popular breeds of dwarf hamsters. Both are considered to be small hamster breeds. The first type is Phodopus campbelli, or the dwarf Campbell Russian hamster.',
    },
    {
        breed: 'Roborovski Dwarf',
        src: '/assets/images/hamsters/roborovski.jpg',
        text: 'Phodopus roborovski, or the Roborovski hamster, is both the smallest hamster breed and undoubtedly the fastest. These incredibly petite dwarf hamsters grow to just 2 and a half inches long.',
    },
    {
        breed: 'Chinese',
        src: '/assets/images/hamsters/chinese.jpg',
        text: 'The Chinese hamster, or Cricetulus griseus, is sometimes also called the striped hamster because of the darker stripe running down the spine. Size-wise, they can grow as long as four inches.',
    },
]

const turtles = [
    {
        breed: 'Red Eared Slider',
        src: '/assets/images/turtles/red-eared.webp',
        text: 'Red Eared Sliders are one of the most popular of all the aquatic turtle species. They tend to be friendlier and more sociable than some of their relatives, they\'re pretty active, and they\'re widely available.',
    },
    {
        breed: 'African Sideneck',
        src: '/assets/images/turtles/african-sideneck.webp',
        text: 'These unique little aquatic turtles have distinctive long necks that can\'t be retracted fully into their shell, and their anatomy differs from traditional water-based turtles.',
    },
    {
        breed: 'Mississippi Map Turtle',
        src: '/assets/images/turtles/mississippi-map.webp',
        text: 'Mississippi Map Turtles have a distinctive dorsal fin running along their shell, and this is why they\'re also sometimes referred to as the \'Sawback\'.',
    },
    {
        breed: 'Reeve\'s Turtle',
        src: '/assets/images/turtles/reeves.webp',
        text: 'The Reeve\'s Turtle is probably one of the most sociable of all the turtles on this list. With care and patience, they sometimes even enjoy being stroked, which is unusual for an aquatic turtle.',
    },
]

export default {
    pages, cats, dogs, hamsters, turtles,
}
