# Generated by Django 4.1.13 on 2024-09-08 10:10

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('users', '0004_message_is_game_invite'),
    ]

    operations = [
        migrations.AddField(
            model_name='player',
            name='auth_42',
            field=models.BooleanField(default=False),
        ),
    ]
