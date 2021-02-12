#include "musicplayer.h"

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QGridLayout>
#include <QProgressBar>
#include <QPushButton>
#include <QSlider>

MusicPlayer::MusicPlayer(QWidget *parent) : QWidget(parent)
{
    auto layout = new QGridLayout(this);
    setLayout(layout);

    auto playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl::fromLocalFile(":/music/Luis Fonsi - Despacito ft. Daddy Yankee.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    auto player = new QMediaPlayer();
    player->setPlaylist(playlist);
    player->stop();

    auto songProgress = new QProgressBar(this);
    songProgress->setOrientation(Qt::Horizontal);
    songProgress->setTextVisible(false);
    songProgress->setStyleSheet("::chunk{background-color:red}");
    songProgress->setValue(0);
    layout->addWidget(songProgress, 2, 0, 2, 2);

    auto playButton = new QPushButton(this);
    playButton->setText("PLAY");
    connect(playButton, &QPushButton::clicked, player, &QMediaPlayer::play);
    layout->addWidget(playButton, 0, 0);

    auto pauseButton = new QPushButton(this);
    pauseButton->setText("PAUSE");
    connect(pauseButton, &QPushButton::clicked, player, &QMediaPlayer::pause);
    layout->addWidget(pauseButton, 0, 1);

    auto volumeSlider = new QSlider(this);
    volumeSlider->setOrientation(Qt::Horizontal);
    volumeSlider->setRange(0, 10);
    volumeSlider->setTickInterval(QSlider::NoTicks);
    connect(volumeSlider, &QSlider::valueChanged, player, &QMediaPlayer::setVolume);
    layout->addWidget(volumeSlider, 1, 0, 1, 2);
}
